
#pragma once

#include "GameObject.h"


#define ITEMHEAL_BBOX_WIDTH			16
#define ITEMHEAL_BBOX_HEIGHT		16

#define ITEMHEAL_ANI_STANDING		0

#define ITEMHEAL_ANI_SETS_ID		90

#define ITEMHEAL_STATE_STANDING		100
#define ITEMHEAL_STATE_DIE			200

#define ITEMHEAL_DYING_TIME			200
#define ITEMHEAL_SPEED				0.035f

class CItemHeal : public CGameObject {


	DWORD die_start = NULL;				//time die animation

public:
	int isDying;

	CItemHeal();
	CItemHeal(float x, float y);
	~CItemHeal();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }
};


