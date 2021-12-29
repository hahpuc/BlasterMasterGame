#include "ItemHeal.h"
#include "Game.h"
#include "Utils.h"
#include "Jason.h"
#include "Player.h"

CItemHeal::CItemHeal()
{

}

CItemHeal::CItemHeal(float x, float y) {
	this->x = x;
	this->y = y;

	isDying = 0;
	SetState(ITEMHEAL_STATE_STANDING);

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEMHEAL_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

void CItemHeal::Render()
{
	if (isFinish && isDying) return;

	int ani = ITEMHEAL_ANI_STANDING;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CItemHeal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + ITEMHEAL_BBOX_WIDTH;
	b = y + ITEMHEAL_BBOX_HEIGHT;
}

void CItemHeal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (isFinish && isDying)	// if dying and die animation finish then return
		return;
}

void CItemHeal::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case ITEMHEAL_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case ITEMHEAL_STATE_STANDING:
		vx = 0; vy = 0;
		break;

	default:
		break;
	}
}

CItemHeal::~CItemHeal()
{

}