#include "SophiaMiddle.h"

CSophiaMiddle::CSophiaMiddle() 
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(1);
	SetAnimationSet(ani_set);
}

CSophiaMiddle::~CSophiaMiddle() {}

void CSophiaMiddle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	
}

void CSophiaMiddle::Render() {
	int ani = PLAYER_ANI_MIDDLE;

	this->animation_set->at(ani)->Render(x, y);
}