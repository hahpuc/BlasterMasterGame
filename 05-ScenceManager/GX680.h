
#pragma once

#include "GameObject.h"
#include "Jason.h"


#define GX680_BBOX_WIDTH		18
#define GX680_BBOX_HEIGHT		17

#define GX680_ANI_STANDING		0
#define GX680_ANI_WALKING		1

#define GX680_ANI_SETS_ID		4

#define GX680_STATE_STANDING	100
#define GX680_STATE_WALKING		200
#define GX680_STATE_DIE			300

#define GX680_DYING_TIME		200
#define GX680_SPEED				0.035f
#define GX680_RANGE				100

class CGX680 : public CGameObject {


	DWORD die_start = NULL;				//time die animation

	float pX, pY;

public:
	int isDying;

	CJason* player;

	CGX680();
	CGX680(float x, float y, CJason* player);
	~CGX680();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }

	void AddItemWhenDie();
};


