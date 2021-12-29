
#pragma once

#include "GameObject.h"
#include "Jason.h"

#define LaserGuard_BBOX_WIDTH		18
#define LaserGuard_BBOX_HEIGHT		17

#define LaserGuard_ANI_STANDING		0

#define LaserGuard_ANI_SETS_ID		6

#define LaserGuard_STATE_STANDING		100
#define LaserGuard_STATE_WALKING		200
#define LaserGuard_STATE_DIE			300

#define LaserGuard_DYING_TIME			200
#define LaserGuard_SPEED				0.035f

class CLaserGuard : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying;

	CLaserGuard();
	CLaserGuard(float x, float y);
	~CLaserGuard();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }
};


