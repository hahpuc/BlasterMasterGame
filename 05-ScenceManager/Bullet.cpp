
#include "Bullet.h"
#include "Game.h"

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

	x += dx;
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