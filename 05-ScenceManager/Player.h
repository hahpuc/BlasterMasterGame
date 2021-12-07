#pragma once
#include "GameObject.h"

#define PLAYER_WALKING_SPEED					0.15f 
//0.1f
#define PLAYER_JUMP_SPEED_Y						0.5f
#define PLAYER_JUMP_DEFLECT_SPEED				0.2f
#define PLAYER_GRAVITY							0.002f
#define PLAYER_DIE_DEFLECT_SPEED				0.5f

#define PLAYER_STATE_IDLE						0
#define PLAYER_STATE_WALKING_RIGHT				100
#define PLAYER_STATE_WALKING_LEFT				200
#define PLAYER_STATE_JUMP						300
#define PLAYER_STATE_DIE						400

#define PLAYER_ANI_BIG_IDLE_RIGHT				0
#define PLAYER_ANI_BIG_IDLE_LEFT				1

#define PLAYER_ANI_WHEEL_STANDING				0
#define PLAYER_ANI_WHEEL_LEFT					1
#define PLAYER_ANI_WHEEL_RIGHT					2
#define PLAYER_ANI_MIDDLE						3
#define PLAYER_ANI_GUN_0						4
#define PLAYER_ANI_GUN_45						5
#define PLAYER_ANI_GUN_90						6
#define PLAYER_ANI_CABIN_STANDING				7
#define PLAYER_ANI_CABIN_WALKING				8

#define PLAYER_ANI_DIE							69

#define	PLAYER_LEVEL_JASON					1
#define	PLAYER_LEVEL_SHOPHIA				2

#define PLAYER_BIG_BBOX_WIDTH				26
#define PLAYER_BIG_BBOX_HEIGHT				18

#define PLAYER_SMALL_BBOX_WIDTH				13
#define PLAYER_SMALL_BBOX_HEIGHT			15

#define PLAYER_UNTOUCHABLE_TIME				5000

#define FALLING_VELOCITY_UPPER_LIMITATION	0.02f


class CSophiaMiddle;
class CSophiaRightWheel;
class CSophiaLeftWheel;
class CSophiaCabin;
class CSophiaGun;


class CPlayer : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	bool isJumping;
	bool isFireBullet = false;

	CSophiaMiddle* middle;
	CSophiaRightWheel* rightWheel;
	CSophiaLeftWheel* leftWheel;
	CSophiaCabin* cabin;
	CSophiaGun* gun;

public:

	CPlayer(float x = 0.0f, float y = 0.0f);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void SetJumping() { isJumping = !isJumping; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	LPANIMATION_SET GetAnimationSet() { return this->animation_set; }

	// Bullet
	CGameObject* NewBullet();

	void FireBullet() { this->isFireBullet = !this->isFireBullet; }
	bool BeingFireBullet() { return isFireBullet; }
};