#pragma once
#include "GameObject.h"
#include "Utils.h"
	
#define JASON_WALKING_SPEED						0.15f 
//0.1f
#define JASON_GRAVITY							0.002f
#define JASON_DIE_DEFLECT_SPEED					0.5f

#define JASON_STATE_IDLE						0
#define JASON_STATE_WALKING_RIGHT				100
#define JASON_STATE_WALKING_LEFT				200					
#define JASON_STATE_WALKING_TOPDOWN				300
#define JASON_STATE_WALKING_TOPUP				400
#define JASON_STATE_DIE							500

#define JASON_ANI_WALKING_TOP_DOWN				0
#define JASON_ANI_WALKING_TOP_UP				1
#define JASON_ANI_WALKING_LEFT					2
#define JASON_ANI_WALKING_RIGHT					3
#define JASON_ANI_IDLE_TOP_DOWN					4
#define JASON_ANI_IDLE_TOP_UP					5
#define JASON_ANI_IDLE_LEFT						6
#define JASON_ANI_IDLE_RIGHT					7


#define JASON_BBOX_WIDTH					24
#define JASON_BBOX_HEIGHT					32

#define JASON_UNTOUCHABLE_TIME				5000

#define FALLING_VELOCITY_UPPER_LIMITATION	0.02f



class CJason : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	DWORD lastShoot;

	float start_x;			// initial position of Mario at scene
	float start_y;

	bool isFireBullet;

public:

	CJason(float x = 0.0f, float y = 0.0f);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	LPANIMATION_SET GetAnimationSet() { return this->animation_set; }

	// Bullet
	CGameObject* NewBullet();

	void FireBullet() { this->isFireBullet = true; }
	void CancelFireBullet() { this->isFireBullet = false; }

	DWORD GetLastShoot() { return this->lastShoot; }
	void SetLastShoot() { this->lastShoot = GetTickCount64(); }


	bool BeingFireBullet() { return isFireBullet; }
};