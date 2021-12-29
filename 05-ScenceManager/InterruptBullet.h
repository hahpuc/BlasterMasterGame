#pragma once
#include "GameObject.h"
#include "Interrupt.h"

#define BULLET_INTERRUPT_BBOX_WIDTH			9
#define BULLET_INTERRUPT_BBOX_HEIGHT		9

#define BULLET_INTERRUPT_ANI				0 

#define BULLET_INTERRUPT_ANI_SETS_ID		25

#define BULLET_INTERRUPT_SPEED				0.25f
#define BULLET_INTERRUPT_GRAVITY			0.001f

#define BULLET_INTERRUPT_STATE_NORMAL		100
#define BULLET_INTERRUPT_STATE_FINISH		301



class CBulletInterrupt : public CGameObject
{


public:

	CInterrupt* parent;

	CBulletInterrupt(CInterrupt* parent);
	void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};