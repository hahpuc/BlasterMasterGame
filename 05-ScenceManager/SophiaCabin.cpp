#include "SophiaCabin.h"

CSophiaCabin::CSophiaCabin(CPlayer* sophia)
{
	this->parent = sophia;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(PLAYER_PART_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

CSophiaCabin::~CSophiaCabin() {}

void CSophiaCabin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void CSophiaCabin::Render() {
	int ani = PLAYER_ANI_CABIN_STANDING;

	float partX, partY;
	parent->GetPosition(partX, partY);

	this->animation_set->at(ani)->Render(partX, partY + 2.0);
}