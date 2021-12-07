#pragma once
#include "Player.h"

#define PLAYER_ANI_STANDING			0
#define PLAYER_ANI_LEFT_WALK		1
#define PLAYER_ANI_RIGHT_WALK		2

#define PLAYER_PART_ANI_SETS_ID		1

class CSophiaRightWheel : public CGameObject {
protected:

	CPlayer* parent;

public:
	CSophiaRightWheel(CPlayer* sophia);
	~CSophiaRightWheel();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

};

