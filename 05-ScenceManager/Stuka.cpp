#include "Stuka.h"
#include "Game.h"
#include "Utils.h"

CStuka::CStuka()
{
	isDying = 0;
	SetState(STUKA_STATE_STANDING);
}

CStuka::CStuka(float x, float y) {
	this->x = x;
	this->y = y;
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
		break;

	default:
		break;
	}
}

CStuka::~CStuka()
{

}