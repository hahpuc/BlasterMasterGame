
#pragma once

#include "GameObject.h"
#include "Player.h"


#define INTERRUPT_BBOX_WIDTH		21
#define INTERRUPT_BBOX_HEIGHT		17

#define INTERRUPT_ANI_STANDING		0

#define INTERRUPT_ANI_SETS_ID		31

#define INTERRUPT_STATE_STANDING	100
#define INTERRUPT_STATE_ACTIVE		300
#define INTERRUPT_STATE_DIE			200

#define INTERRUPT_BULLET_TYPE		80

class CInterrupt : public CGameObject {


	DWORD die_start = NULL;				//time die animation



	float pX, pY;   // Player position
public:
	int isDying ;
	bool isFireBullet;
	DWORD lastShoot;

	CPlayer* player;

	CInterrupt();
	CInterrupt(float x, float y, CPlayer* player);
	~CInterrupt();

	CGameObject* NewBullet();

	void SetFireBullet() { this->isFireBullet = true; }
	void CancleFireBullet() { this->isFireBullet = false; }
	DWORD GetLastShoot() { return this->lastShoot; }
	void SetLastShoot() { this->lastShoot = GetTickCount64(); }

	virtual void SetState(int state);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartDying() { isDying = 1; die_start = DWORD(GetTickCount64()); }

	void AddItemWhenDie();

};


