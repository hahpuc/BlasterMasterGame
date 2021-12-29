
#include "InterruptBullet.h"
#include "Game.h"
#include "Brick.h"
#include "Utils.h"
#include "Player.h"
#include "Bullet.h"

CBulletInterrupt::CBulletInterrupt(CInterrupt* parent) {
	vy = BULLET_INTERRUPT_SPEED;

	this->parent = parent;
	this->SetState(BULLET_INTERRUPT_STATE_NORMAL);

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(BULLET_INTERRUPT_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

void CBulletInterrupt::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish)
		return;

	l = x;
	t = y;
	r = x + BULLET_INTERRUPT_BBOX_WIDTH;
	b = y + BULLET_INTERRUPT_BBOX_HEIGHT;
}

void CBulletInterrupt::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float camx, camy;
	float screenHeight = game->GetScreenHeight();
	float screenWidth = game->GetScreenWidth();
	game->GetCamPos(camx, camy);


	// DELETE bullet if out of map 
	if (x < camx || x > camx + screenWidth)
		isFinish = 1;
	if (y < camy || y > camy + screenHeight)
		isFinish = 1;

	if (isFinish || this->state == BULLET_INTERRUPT_STATE_FINISH)
		return;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny = 1;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (int i = 0; i < coEventsResult.size(); ++i) {
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{	
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				this->SetState(BULLET_INTERRUPT_STATE_FINISH);
			}
			else

			if (dynamic_cast<CPlayer*>(e->obj))
			{
				CPlayer* player = dynamic_cast<CPlayer*>(e->obj);
				if (player->GetIsUntouchable())
					continue;

				player->StartUntouchable();
				this->SetState(BULLET_INTERRUPT_STATE_FINISH);

				player->DecreaseHeal(10);
			}
			//if (dynamic_cast<CPlayer*>(e->obj))				// object is Brick
			//{
			//	CPlayer* player = dynamic_cast<CPlayer*>(e->obj);
			//	this->SetState(BULLET_INTERRUPT_STATE_FINISH);
			//	player->DecreaseHeal(10);
			//}
			else
			if (dynamic_cast<CBullet*>(e->obj))				// object is Brick
			{
				CBullet* bullet = dynamic_cast<CBullet*>(e->obj);
				this->SetState(BULLET_INTERRUPT_STATE_FINISH);
				bullet->SetState(BULLET_STATE_FINISH);
			}
		}
	}
}

void CBulletInterrupt::Render()
{
	if (isFinish)
		return;

	int ani = BULLET_INTERRUPT_ANI;

	animation_set->at(ani)->Render(round(x), round(y));
	//RenderBoundingBox(); 
}

void CBulletInterrupt::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case BULLET_INTERRUPT_STATE_NORMAL:
		vx = 0;
		vy = BULLET_INTERRUPT_SPEED;
		ny = 1;
		nx = 0;
		break;

	case BULLET_INTERRUPT_STATE_FINISH:
		vx = 0;
		vy = 0;
		nx = 0; ny = 0;
		isFinish = 1;
		break;

	default:
		break;
	}
}