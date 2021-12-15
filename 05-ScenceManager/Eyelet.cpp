#include "Eyelet.h"
#include "Game.h"
#include "Utils.h"
#include "Brick.h"

CEyelet::CEyelet()
{
	
}

CEyelet::CEyelet(float x, float y) {
	this->x = x;
	this->y = y;

	isDying = 0;
	SetState(EYELET_STATE_WALKING);
}

void CEyelet::Render()
{
	if (isFinish && isDying) return;

	int ani = EYELET_ANI_LEFT;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CEyelet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + EYELET_BBOX_WIDTH;
	b = y + EYELET_BBOX_HEIGHT;
}

void CEyelet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float screenWidth = float(game->GetScreenWidth());
	float screenHeight = float(game->GetScreenHeight());
	game->GetCamPos(camx, camy);

	if (isFinish && isDying)	// if dying and die animation finish then return
		return;

	CGameObject::Update(dt);

	// DIE
	if (state == EYELET_STATE_DIE) {
		if (GetTickCount64() - die_start > EYELET_DYING_TIME) {
			die_start = 0;
			isDying = 1;
		}
	}
	
	if (count >= 180) count = 0;

	if (state == EYELET_STATE_WALKING) {
		vy = EYELET_SPEED * cos(PI + count * PI / 180);
		count++;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != EYELET_STATE_DIE)
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
		}
	}
}

void CEyelet::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case EYELET_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case EYELET_STATE_WALKING:
		vx = EYELET_SPEED;
		break;

	default:
		break;
	}
}

CEyelet::~CEyelet()
{

}