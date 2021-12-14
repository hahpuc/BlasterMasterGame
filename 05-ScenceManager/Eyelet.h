
#pragma once

#include "GameObject.h"


#define EYELET_BBOX_WIDTH		18
#define EYELET_BBOX_HEIGHT		17

#define EYELET_ANI_RIGHT		0
#define EYELET_ANI_LEFT			1

#define EYELET_ANI_SETS_ID		34

#define EYELET_STATE_STANDING		100
#define EYELET_STATE_DIE			200

class CEyelet : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying;

	CEyelet();
	CEyelet(float x, float y);
	~CEyelet();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }
};


