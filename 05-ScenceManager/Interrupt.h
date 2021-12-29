
#pragma once

#include "GameObject.h"


#define INTERRUPT_BBOX_WIDTH		21
#define INTERRUPT_BBOX_HEIGHT		17

#define INTERRUPT_ANI_STANDING		0

#define INTERRUPT_ANI_SETS_ID		31

#define INTERRUPT_STATE_STANDING	100
#define INTERRUPT_STATE_DIE			200

class CInterrupt : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying ;

	CInterrupt();
	CInterrupt(float x, float y);
	~CInterrupt();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }

	void AddItemWhenDie();

};


