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

	float transX = 12.0, transY = -8.0;

	if (parent->GetState() == PLAYER_STATE_HEAD_UP) {
		ani = PLAYER_ANI_GUN_90;
		transX = 0.0;
		transY = -18.0;
	}
	else {
		if (nx > 0)
			ani = PLAYER_ANI_GUN_0_RIGHT;
		else
			ani = PLAYER_ANI_GUN_0_LEFT;
	}
	

	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += PLAYER_BIG_BBOX_WIDTH / 2;
	partY += PLAYER_BIG_BBOX_HEIGHT / 2;

	int alpha = 255;
	if (parent->GetIsUntouchable()) alpha = 128;

	this->animation_set->at(ani)->Render(partX + nx * transX, partY + transY, alpha);
}