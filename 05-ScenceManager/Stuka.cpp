#include "Stuka.h"
#include "Game.h"
#include "Utils.h"
#include "Brick.h"

CStuka::CStuka()
{
	
}

CStuka::CStuka(float x, float y) {
	this->x = x;
	this->y = y;

	vx = STUKA_SPEED;
	isDying = 0;
	SetState(STUKA_STATE_STANDING);
}

void CStuka::Render()
{
	if (isFinish && isDying) return;

	int ani = STUKA_ANI_STANDING;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CStuka::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + STUKA_BBOX_WIDTH;
	b = y + STUKA_BBOX_HEIGHT;
}

void CStuka::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float screenWidth = float(game->GetScreenWidth());
	float screenHeight = float(game->GetScreenHeight());
	game->GetCamPos(camx, camy);


	if (isFinish && isDying)	// if dying and die animation finish then return
		return;

	CGameObject::Update(dt);

	if (state == STUKA_DYING_TIME) {
		if (GetTickCount64() - die_start > STUKA_DYING_TIME) {
			die_start = 0; 
			isDying = 1;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != STUKA_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
			x += dx;
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

			 if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				vx = -vx;
			}
		}
	}
}

void CStuka::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case STUKA_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case STUKA_STATE_STANDING:
		vx = STUKA_SPEED;
		break;

	default:
		break;
	}
}

CStuka::~CStuka()
{

}