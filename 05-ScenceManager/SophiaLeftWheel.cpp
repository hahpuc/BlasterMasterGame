#include "SophiaLeftWheel.h"

CSophiaLeftWheel::CSophiaLeftWheel(CPlayer* sophia)
{
	this->parent = sophia;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(PLAYER_PART_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

CSophiaLeftWheel::~CSophiaLeftWheel() {}

void CSophiaLeftWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void CSophiaLeftWheel::Render() {
	int ani = PLAYER_ANI_RIGHT_WALK;

	float partX, partY;
	parent->GetPosition(partX, partY);

	this->animation_set->at(ani)->Render(partX - 8.0, partY + 11.0);
}