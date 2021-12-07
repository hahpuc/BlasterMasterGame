#include "SophiaMiddle.h"

CSophiaMiddle::CSophiaMiddle(CPlayer* sophia) 
{
	this->parent = sophia;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(PLAYER_PART_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

CSophiaMiddle::~CSophiaMiddle() {}

void CSophiaMiddle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	nx = parent->GetDirection();
}

void CSophiaMiddle::Render() {
	int ani = PLAYER_ANI_MIDDLE;

	float partX, partY;
	parent->GetPosition(partX, partY);

	this->animation_set->at(ani)->Render(partX, partY + 11.0);
}