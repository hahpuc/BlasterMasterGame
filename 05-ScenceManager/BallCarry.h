
#pragma once

#include "GameObject.h"
#include "Player.h"


#define BALLCARRY_BBOX_WIDTH		18
#define BALLCARRY_BBOX_HEIGHT		17

#define BALLCARRY_ANI_RIGHT			0
#define BALLCARRY_ANI_LEFT			1
#define BALLCARRY_ANI_ACTIVE		2

#define BALLCARRY_ANI_SETS_ID		35

#define BALLCARRY_STATE_STANDING	100
#define BALLCARRY_STATE_DIE			200
#define BALLCARRY_STATE_ACTIVE		303

#define BALLCARRY_SPEED			0.035f


#define BALLCARRY_RANGE				150
#define OBJECT_TYPE_BOMB			81

class CBallCarry : public CGameObject {


	DWORD die_start = NULL;				//time die animation
	float pX, pY;						// position of player
public:
	int isDying;

	bool isFireBomb;
	DWORD lastBomb;


	CPlayer* player;

	CBallCarry();
	CBallCarry(float x, float y, CPlayer* player);
	~CBallCarry();

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }

	// BOMB
	CGameObject* NewBomb(float x, float y, int nx);

	void SetBomb() { this->isFireBomb = true; }
	void CancleBomb() { this->isFireBomb = false; }
	DWORD GetLastBomb() { return this->lastBomb; }
	void SetLastBomb() { this->lastBomb = GetTickCount64(); }
};


