
#pragma once

#include "GameObject.h"


#define STUKA_BBOX_WIDTH		18
#define STUKA_BBOX_HEIGHT		17

#define STUKA_ANI_STANDING		0

#define STUKA_ANI_SETS_ID		33

#define STUKA_STATE_STANDING	100
#define STUKA_STATE_DIE			200

class CStuka : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying;

	CStuka();
	CStuka(float x, float y);
	~CStuka();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }
};


