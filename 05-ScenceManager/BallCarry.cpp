#include "BallCarry.h"
#include "Game.h"
#include "Utils.h"

CBallCarry::CBallCarry()
{
	isDying = 0;
	SetState(BALLCARRY_STATE_STANDING);
}

CBallCarry::CBallCarry(float x, float y) {
	this->x = x;
	this->y = y;
}

void CBallCarry::Render()
{
	if (isFinish && isDying) return;

	int ani = BALLCARRY_ANI_RIGHT;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CBallCarry::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + BALLCARRY_BBOX_WIDTH;
	b = y + BALLCARRY_BBOX_HEIGHT;
}

void CBallCarry::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float screenWidth = float(game->GetScreenWidth());
	float screenHeight = float(game->GetScreenHeight());
	game->GetCamPos(camx, camy);


	if (isFinish && isDying)	// if dying and die animation finish then return
		return;

	CGameObject::Update(dt);
}

void CBallCarry::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case BALLCARRY_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case BALLCARRY_STATE_STANDING:
		break;

	default:
		break;
	}
}

CBallCarry::~CBallCarry()
{

}