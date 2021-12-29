#include "GX680S.h"
#include "Game.h"
#include "Utils.h"
#include "Brick.h"

CGX680S::CGX680S()
{

}

CGX680S::CGX680S(float x, float y, CJason* player) {
	this->x = x;
	this->y = y;
	this->player = player;

	vx = GX680S_SPEED;
	isDying = 0;
	SetState(GX680S_STATE_STANDING);
}

void CGX680S::Render()
{
	if (isFinish && isDying) return;

	int ani = GX680S_ANI_STANDING;

	if (this->GetState() == GX680S_STATE_WALKING)
		ani = GX680S_ANI_WALKING;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CGX680S::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + GX680S_BBOX_WIDTH;
	b = y + GX680S_BBOX_HEIGHT;
}

void CGX680S::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float screenWidth = float(game->GetScreenWidth());
	float screenHeight = float(game->GetScreenHeight());
	game->GetCamPos(camx, camy);


	if (isFinish && isDying)	// if dying and die animation finish then return
		return;

	this->player->GetPosition(pX, pY);

	CGameObject::Update(dt);

	if ((abs(x - pX) < GX680S_RANGE || abs(y - pY) < GX680S_RANGE) && state == GX680S_STATE_STANDING)
	{
		SetState(GX680S_STATE_WALKING);
	}

	if (state == GX680S_DYING_TIME) {
		if (GetTickCount64() - die_start > GX680S_DYING_TIME) {
			die_start = 0;
			isDying = 1;
		}
	}

	if (state == GX680S_STATE_WALKING)
	{
		if (abs(x - pX) > GX680S_RANGE || abs(y - pY) > GX680S_RANGE)
		{
			SetState(GX680S_STATE_STANDING);
		}
	}

	if (state == GX680S_DYING_TIME) {
		if (GetTickCount64() - die_start > GX680S_DYING_TIME) {
			die_start = 0;
			isDying = 1;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != GX680S_STATE_DIE)
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
				if (e->nx != 0 && e->ny == 0)
				{
					vx = GX680S_SPEED * e->nx;
				}
			}
			else
			if (dynamic_cast<CJason*>(e->obj))
			{
				CJason* jason = dynamic_cast<CJason*>(e->obj);
				jason->DecreaseHeal(10);
			}
		}
	}
}

void CGX680S::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case GX680S_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case GX680S_STATE_STANDING:
		vx = 0;
		vy = 0;
		break;

	case GX680S_STATE_WALKING:
		if ((pX - x) > 0) vx = GX680S_SPEED;
		else
		if ((pX - x) < 0) vx = -GX680S_SPEED;

		if ((pY - y) > 0) vy = GX680S_SPEED;
		else
		if ((pY - y) < 0) vy = -GX680S_SPEED;
		break;

	default:
		break;
	}
}

CGX680S::~CGX680S()
{

}