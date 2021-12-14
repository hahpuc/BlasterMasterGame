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
	int ani = PLAYER_ANI_CABIN_STANDING_RIGHT;
	float transX = 0, transY = 0;

	if (parent->GetState() == PLAYER_STATE_HEAD_UP) {
		if (nx > 0) {
			ani = PLAYER_ANI_CABIN_HEAD_RIGHT;
			transX = -8.0;
		}
			
		else {
			ani = PLAYER_ANI_CABIN_HEAD_LEFT;
			transX = 0.0;
		}
		
		transY = -14.0;
	}
	else {
		if (nx > 0)
			ani = PLAYER_ANI_CABIN_STANDING_RIGHT;
		else
			ani = PLAYER_ANI_CABIN_STANDING_LEFT;

		transX = -4.0;
		transY = -8.0;
	}
		

	float partX, partY;
	parent->GetPosition(partX, partY);

	partX += PLAYER_BIG_BBOX_WIDTH / 2;
	partY += PLAYER_BIG_BBOX_HEIGHT / 2;

	this->animation_set->at(ani)->Render(partX + transX, partY + transY);
}