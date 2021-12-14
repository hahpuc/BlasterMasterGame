#include "Eyelet.h"
#include "Game.h"
#include "Utils.h"

CEyelet::CEyelet()
{
	isDying = 0;
	SetState(EYELET_STATE_STANDING);
}

CEyelet::CEyelet(float x, float y) {
	this->x = x;
	this->y = y;
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
	case EYELET_STATE_STANDING:
		break;

	default:
		break;
	}
}

CEyelet::~CEyelet()
{

}