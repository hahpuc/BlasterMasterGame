#include "SophiaGun.h"

CSophiaGun::CSophiaGun(CPlayer* sophia)
{
	this->parent = sophia;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(PLAYER_PART_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

CSophiaGun::~CSophiaGun() {}

void CSophiaGun::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void CSophiaGun::Render() {
	int ani = PLAYER_ANI_GUN_0;

	float partX, partY;
	parent->GetPosition(partX, partY);

	this->animation_set->at(ani)->Render(partX - 7.5, partY + 2.0);
}