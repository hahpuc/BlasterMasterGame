
#include "Bullet.h"
#include "Game.h"
#include "Interrupt.h"
#include "Brick.h"

CBullet::CBullet(int nx) {
	vx = BULLET_SPEED * nx;
	this->nx = nx;
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish)
		return;

	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	if (isFinish)
		return;

	CGameObject::Update(dt);

	vy += BULLET_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		//y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		for (int i = 0; i < coEventsResult.size(); ++i) {
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CInterrupt*>(e->obj)) {   // If object is Interrupt
				isFinish = 1;
				CInterrupt* interrupt = dynamic_cast<CInterrupt*>(e->obj);
				interrupt->SetState(INTERRUPT_STATE_DIE);
			}
			else if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx != 0 && this->y >= brick->y)
					isFinish = 1;
				else
					isFinish = 0;
			}
		}
	}
}

void CBullet::Render()
{
	if (isFinish)
		return;

	int ani = BULLET_ANI_RIGHT_LV3;

	if (vx > 0) ani = BULLET_ANI_RIGHT_LV3;
	else if (vx <= 0) ani = BULLET_ANI_LEFT_LV3;

	animation_set->at(ani)->Render(round(x), round(y));
	//RenderBoundingBox();
}

void CBullet::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case BULLET_STATE_NORMAL: 
		vx = BULLET_SPEED;
		break;

	default:
		break;
	}
}