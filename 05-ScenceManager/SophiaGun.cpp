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
	int ani = PLAYER_ANI_GUN_0_RIGHT;

	if (nx > 0)
		ani = PLAYER_ANI_GUN_0_RIGHT;
	else
		ani = PLAYER_ANI_GUN_0_LEFT;

	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += PLAYER_BIG_BBOX_WIDTH / 2;
	partY += PLAYER_BIG_BBOX_HEIGHT / 2;

	this->animation_set->at(ani)->Render(partX + nx*12.0, partY - 8.0);
}