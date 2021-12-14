
#pragma once

#include "GameObject.h"


#define BALLCARRY_BBOX_WIDTH		18
#define BALLCARRY_BBOX_HEIGHT		17

#define BALLCARRY_ANI_RIGHT			0
#define BALLCARRY_ANI_LEFT			1

#define BALLCARRY_ANI_SETS_ID		35

#define BALLCARRY_STATE_STANDING	100
#define BALLCARRY_STATE_DIE			200

class CBallCarry : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying;

	CBallCarry();
	CBallCarry(float x, float y);
	~CBallCarry();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }
};


