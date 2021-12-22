
#pragma once

#include "GameObject.h"


#define GX680S_BBOX_WIDTH		18
#define GX680S_BBOX_HEIGHT		17

#define GX680S_ANI_STANDING		0
#define GX680S_ANI_WALKING		1

#define GX680S_ANI_SETS_ID		5

#define GX680S_STATE_STANDING		100
#define GX680S_STATE_WALKING		200
#define GX680S_STATE_DIE			300

#define GX680S_DYING_TIME			200
#define GX680S_SPEED				0.035f

class CGX680S : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying;

	CGX680S();
	CGX680S(float x, float y);
	~CGX680S();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }
};

