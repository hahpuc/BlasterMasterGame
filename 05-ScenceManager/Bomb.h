#pragma once
#include "GameObject.h"
#include "BallCarry.h"

#define BOMB_BBOX_WIDTH			10
#define BOMB_BBOX_HEIGHT		10

#define BOMB_ANI_NORMAL			3 
#define BOMB_ANI_FINISH			4

#define BOMB_ANI_SETS_ID		35

#define BOMB_SPEED				0.15f
#define BOMB_GRAVITY			0.001f

#define BOMB_STATE_NORMAL		100
#define BOMB_STATE_FINISH		309



class CBomb : public CGameObject
{


public:

	CBallCarry* parent;

	CBomb(CBallCarry* parent, int nx);
	void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};