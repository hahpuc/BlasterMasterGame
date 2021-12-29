#include "Interrupt.h"
#include "Game.h"
#include "Utils.h"

CInterrupt::CInterrupt()
{
	isDying = 0;
	SetState(INTERRUPT_STATE_STANDING);
	isAddedItem = 0;

}

CInterrupt::CInterrupt(float x, float y) {
	this->x = x;
	this->y = y;
}

void CInterrupt::Render()
{
	if (isFinish && isDying) return;

	int ani = INTERRUPT_ANI_STANDING;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CInterrupt::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + INTERRUPT_BBOX_WIDTH;
	b = y + INTERRUPT_BBOX_HEIGHT;
}

void CInterrupt::AddItemWhenDie() {
	LPSCENE currentScene = CGame::GetInstance()->GetCurrentScene();
	currentScene->isAddedItem = false;
	currentScene->AddItemAt(this->x, this->y);
}

void CInterrupt::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float screenWidth = float(game->GetScreenWidth());
	float screenHeight = float(game->GetScreenHeight());
	game->GetCamPos(camx, camy);


	if (isFinish && isDying && !isAddedItem) {
		this->AddItemWhenDie();
		isAddedItem = 1;
		return;
	}

	CGameObject::Update(dt);
}

void CInterrupt::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case INTERRUPT_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case INTERRUPT_STATE_STANDING:
		break;
	
	default:
		break;
	}
}

CInterrupt::~CInterrupt()
{

}