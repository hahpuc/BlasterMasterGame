
#pragma once

#include "GameObject.h"


#define BALLBOT_BBOX_WIDTH			18
#define BALLBOT_BBOX_HEIGHT			17

#define BALLBOT_ANI_STANDING		0

#define BALLBOT_ANI_SETS_ID			32

#define BALLBOT_STATE_STANDING		100
#define BALLBOT_STATE_DIE			200

class CBallBot : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying;

	CBallBot();
	CBallBot(float x, float y);
	~CBallBot();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }
};


