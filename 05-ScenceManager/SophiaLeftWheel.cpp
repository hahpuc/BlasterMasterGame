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
	int ani = PLAYER_ANI_LEFT_WALK;

	float transX = -7.0, transY = 0;

	if (parent->GetState() == PLAYER_STATE_IDLE) {
		ani = PLAYER_ANI_STANDING;
	}
	else if (parent->GetState() == PLAYER_STATE_WALKING_RIGHT) {
		ani = PLAYER_ANI_RIGHT_WALK;
	}
	else if (parent->GetState() == PLAYER_STATE_WALKING_LEFT) {
		ani = PLAYER_ANI_LEFT_WALK;
	}
	else if (parent->GetState() == PLAYER_STATE_HEAD_UP) {
		ani = PLAYER_ANI_STANDING;
		transX = -5.0;
	}


	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += PLAYER_BIG_BBOX_WIDTH / 2;
	partY += PLAYER_BIG_BBOX_HEIGHT / 2;

	this->animation_set->at(ani)->Render(partX + transX, partY);
}