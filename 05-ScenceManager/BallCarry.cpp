#include "BallCarry.h"
#include "Game.h"
#include "Utils.h"
#include "Bomb.h"
#include "Brick.h"

CBallCarry::CBallCarry()
{
	isDying = 0;
	SetState(BALLCARRY_STATE_STANDING);
}

CBallCarry::CBallCarry(float x, float y, CPlayer* player) {
	this->x = x;
	this->y = y;

	this->vx = BALLCARRY_SPEED;

	this->player = player;
}

void CBallCarry::Render()
{
	if (isFinish && isDying) return;

	int ani = BALLCARRY_ANI_RIGHT;

	if (this->state == BALLCARRY_STATE_ACTIVE)
		ani = BALLCARRY_ANI_ACTIVE;
	else
	if (this->state == BALLCARRY_STATE_STANDING)
		ani = BALLCARRY_ANI_RIGHT;

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
	if (isFinish && isDying)	// if dying and die animation finish then return
		return;

	CGameObject::Update(dt);

	this->player->GetPosition(pX, pY);

	// If person under Interrupt
	float rangeTop = this->y;
	float rangeDown = this->y + BALLCARRY_BBOX_HEIGHT;

	if (rangeTop - 8 <= pY && pY <= rangeDown + 8 && abs(x - pX) <= BALLCARRY_RANGE)
		this->SetState(BALLCARRY_STATE_ACTIVE);
	else
		this->SetState(BALLCARRY_STATE_STANDING);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != BALLCARRY_STATE_DIE)
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
		this->CancleBomb();
		break;

	case BALLCARRY_STATE_ACTIVE: 
		vx = BALLCARRY_SPEED;
		this->SetBomb();
		break;

	default:
		break;
	}
}

CGameObject* CBallCarry::NewBomb(float x, float y, int nx) {
	DebugOut(L"New bomb at %f, %f \n", x, y);

	CGameObject* obj = new CBomb(this, nx);

	obj->type = OBJECT_TYPE_BOMB;

	obj->SetPosition(x , y);

	return obj;
}

CBallCarry::~CBallCarry()
{

}