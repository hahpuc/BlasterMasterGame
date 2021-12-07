#pragma once
#include "Player.h"

#define PLAYER_ANI_CABIN_STANDING_LEFT			7
#define PLAYER_ANI_CABIN_WALKING_LEFT			8
#define PLAYER_ANI_CABIN_STANDING_RIGHT			11
#define PLAYER_ANI_CABIN_WALKING_RIGHT			12

#define PLAYER_PART_ANI_SETS_ID		1

class CSophiaCabin : public CGameObject {
protected:

	CPlayer* parent;

public:
	CSophiaCabin(CPlayer* sophia);
	~CSophiaCabin();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

};

