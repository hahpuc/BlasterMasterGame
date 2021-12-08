#include "SophiaRightWheel.h"

CSophiaRightWheel::CSophiaRightWheel(CPlayer* sophia)
{
	this->parent = sophia;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(PLAYER_PART_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}

CSophiaRightWheel::~CSophiaRightWheel() {}

void CSophiaRightWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = parent->GetDirection();
}

void CSophiaRightWheel::Render() {
	int ani = PLAYER_ANI_LEFT_WALK;

	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += PLAYER_BIG_BBOX_WIDTH / 2;
	partY += PLAYER_BIG_BBOX_HEIGHT / 2;

	this->animation_set->at(ani)->Render(partX + 7.0, partY);
}