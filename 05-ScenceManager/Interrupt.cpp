#include "Interrupt.h"
#include "Game.h"
#include "Utils.h"
#include "InterruptBullet.h"

CInterrupt::CInterrupt()
{
	isDying = 0;
	SetState(INTERRUPT_STATE_STANDING);
	isAddedItem = 0;

}

CInterrupt::CInterrupt(float x, float y, CPlayer* player) {
	this->x = x;
	this->y = y;

	this->player = player;
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
	if (isFinish && isDying && !isAddedItem) {
		this->AddItemWhenDie();
		isAddedItem = 1;
		return;
	}

	this->player->GetPosition(pX, pY);

	CGameObject::Update(dt);

	// If person under Interrupt
	float rangeLeft = this->x; 
	float rangeRight = this->x + INTERRUPT_BBOX_WIDTH;

	if (rangeLeft - 8 <= pX && pX <= rangeRight - 8 && this->y < pY)
		this->SetState(INTERRUPT_STATE_ACTIVE);
	else
		this->SetState(INTERRUPT_STATE_STANDING);
}

void CInterrupt::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case INTERRUPT_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		this->CancleFireBullet();
		StartDying();
		break;
	case INTERRUPT_STATE_STANDING:
		this->CancleFireBullet();
		break;

	case INTERRUPT_STATE_ACTIVE:
		this->SetFireBullet();
		break;
	
	default:
		break;
	}
}


CGameObject* CInterrupt::NewBullet() {

	DebugOut(L"Interrupt NEW BULLET\n");
	CGameObject* obj = new CBulletInterrupt(this);

	obj->type = INTERRUPT_BULLET_TYPE;

	float transX = INTERRUPT_BBOX_WIDTH / 2;
	float transY = INTERRUPT_BBOX_HEIGHT / 2;
	obj->SetPosition(this->x + transX, this->y + transY);

	return obj;
}

CInterrupt::~CInterrupt()
{

}