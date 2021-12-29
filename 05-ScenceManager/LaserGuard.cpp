#include "LaserGuard.h"
#include "Game.h"
#include "Utils.h"
#include "Brick.h"

CLaserGuard::CLaserGuard()
{

}

CLaserGuard::CLaserGuard(float x, float y) {
	this->x = x;
	this->y = y;

	vx = LaserGuard_SPEED;
	isDying = 0;
	SetState(LaserGuard_STATE_STANDING);
}

void CLaserGuard::Render()
{
	if (isFinish && isDying) return;

	int ani = LaserGuard_ANI_STANDING;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CLaserGuard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + LaserGuard_BBOX_WIDTH;
	b = y + LaserGuard_BBOX_HEIGHT;
}

void CLaserGuard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float screenWidth = float(game->GetScreenWidth());
	float screenHeight = float(game->GetScreenHeight());
	game->GetCamPos(camx, camy);


	if (isFinish && isDying)	// if dying and die animation finish then return
		return;

	CGameObject::Update(dt);

	if (state == LaserGuard_DYING_TIME) {
		if (GetTickCount64() - die_start > LaserGuard_DYING_TIME) {
			die_start = 0;
			isDying = 1;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != LaserGuard_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		for (int i = 0; i < coEventsResult.size(); ++i) {
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				vx = -vx;
			}
			else
			if (dynamic_cast<CJason*>(e->obj))
			{
				CJason* jason = dynamic_cast<CJason*>(e->obj);
				if (jason->GetIsUntouchable())
					continue;

				jason->StartUntouchable();
				jason->DecreaseHeal(10);
			}
		}
	}
}

void CLaserGuard::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case LaserGuard_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case LaserGuard_STATE_STANDING:
		vx = 0;
		vy = 0;
		break;

	case LaserGuard_STATE_WALKING:
		vx = LaserGuard_SPEED;
		break;

	default:
		break;
	}
}

CLaserGuard::~CLaserGuard()
{

}