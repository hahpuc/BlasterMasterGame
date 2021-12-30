
#include "Bomb.h"
#include "Game.h"
#include "Brick.h"
#include "Utils.h"
#include "Player.h"
#include "Bullet.h"

CBomb::CBomb(CBallCarry* parent, int nx) {
	this->parent = parent;
	this->nx = nx;

	vx = BOMB_SPEED * this->nx;
	this->SetState(BOMB_STATE_NORMAL);

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(BOMB_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

void CBomb::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish)
		return;

	l = x;
	t = y;
	r = x + BOMB_BBOX_WIDTH;
	b = y + BOMB_BBOX_HEIGHT;
}

void CBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	if (isFinish || this->state == BOMB_STATE_FINISH)
		return;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
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
				this->SetState(BOMB_STATE_FINISH);
			}
			else
			if (dynamic_cast<CPlayer*>(e->obj))
			{
				CPlayer* player = dynamic_cast<CPlayer*>(e->obj);
				if (player->GetIsUntouchable())
					continue;

				player->StartUntouchable();
				this->SetState(BOMB_STATE_FINISH);

				player->DecreaseHeal(10);
			}
	
		}
	}
}

void CBomb::Render()
{
	if (isFinish)
		return;

	int ani = BOMB_ANI_NORMAL;


	if (this->state == BOMB_STATE_FINISH) {
		ani = BOMB_ANI_FINISH;
		this->isFinish = 1;
	}
	else
	if (this->state == BOMB_STATE_NORMAL) {
		ani = BOMB_ANI_NORMAL;
	}
	

	animation_set->at(ani)->Render(round(x), round(y));
	//RenderBoundingBox(); 
}

void CBomb::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case BOMB_STATE_NORMAL:
		vx = BOMB_SPEED * this->nx;
		vy = 0;
		break;

	case BOMB_STATE_FINISH:
		vx = 0;
		vy = 0;
		nx = 0; ny = 0;
		isFinish = 1;
		break;

	default:
		break;
	}
}