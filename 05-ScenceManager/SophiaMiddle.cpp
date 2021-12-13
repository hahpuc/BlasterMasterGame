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
	float transX = 0, transY = 0;

	if (parent->GetState() == PLAYER_STATE_HEAD_UP) {
		transX = 0;
		transY = -3.0;
	}
	else {

		transX = 0;
		transY = 0;
	}

	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += PLAYER_BIG_BBOX_WIDTH / 2;
	partY += PLAYER_BIG_BBOX_HEIGHT / 2;

	this->animation_set->at(ani)->Render(partX + transX, partY + transY);
}