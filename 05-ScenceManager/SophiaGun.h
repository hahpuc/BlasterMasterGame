#pragma once
#include "Player.h"

#define PLAYER_ANI_GUN_0_LEFT			4
#define PLAYER_ANI_GUN_45_LEFT			5
#define PLAYER_ANI_GUN_90_LEFT			6

#define PLAYER_ANI_GUN_0_RIGHT			9
#define PLAYER_ANI_GUN_45_RIGHT			10

#define PLAYER_PART_ANI_SETS_ID		1

class CSophiaGun : public CGameObject {
protected:

	CPlayer* parent;

public:
	CSophiaGun(CPlayer* sophia);
	~CSophiaGun();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

};

