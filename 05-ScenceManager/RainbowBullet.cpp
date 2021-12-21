
#include "RainbowBullet.h"
#include "Game.h"
#include "Brick.h"


CRainbowBullet::CRainbowBullet(int nx, CJason* parent) {
	vx = RAINBOW_BULLET_SPEED * nx;

	this->nx = nx;

	this->parent = parent;
}

void CRainbowBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish)
		return;

	l = x;
	t = y;
	r = x + RAINBOW_BULLET_BBOX_WIDTH;
	b = y + RAINBOW_BULLET_BBOX_HEIGHT;
}

void CRainbowBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (int i = 0; i < coEventsResult.size(); ++i) {
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				isFinish = 1;
			}
		}
	}
}

void CRainbowBullet::Render()
{
	if (isFinish)
		return;

	int ani = RAINBOW_BULLET_ANI_FIRE;

	animation_set->at(ani)->Render(round(x), round(y));
	//RenderBoundingBox(); 
}

void CRainbowBullet::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case RAINBOW_BULLET_STATE_RIGHT:
		vx = RAINBOW_BULLET_SPEED * nx;
		vy = 0;
		break;
	
	case RAINBOW_BULLET_STATE_LEFT:
		vx = RAINBOW_BULLET_SPEED * nx;
		vy = 0;
		break;

	case RAINBOW_BULLET_STATE_TOP_UP:
		vx = 0;
		vy = RAINBOW_BULLET_SPEED * nx;
		break;

	case RAINBOW_BULLET_STATE_TOP_DOWN:
		vx = 0;
		vy = RAINBOW_BULLET_SPEED * nx;
		break;

	default:
		break;
	}
}