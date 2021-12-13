#include "BallBot.h"
#include "Game.h"
#include "Utils.h"

CBallBot::CBallBot()
{
	isDying = 0;
	SetState(BALLBOT_STATE_STANDING);
}

CBallBot::CBallBot(float x, float y) {
	this->x = x;
	this->y = y;
}

void CBallBot::Render()
{
	if (isFinish && isDying) return;

	int ani = BALLBOT_ANI_STANDING;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CBallBot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + BALLBOT_BBOX_WIDTH;
	b = y + BALLBOT_BBOX_HEIGHT;
}

void CBallBot::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
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

void CBallBot::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case BALLBOT_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case BALLBOT_STATE_STANDING:
		break;

	default:
		break;
	}
}

CBallBot::~CBallBot()
{

}