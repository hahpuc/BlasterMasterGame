#pragma once
#include "Player.h"

#define PLAYER_ANI_MIDDLE			3

#define PLAYER_PART_ANI_SETS_ID		1

class CSophiaMiddle : public CGameObject {
protected:

	CPlayer* parent;

public:
	CSophiaMiddle(CPlayer *sophia);
	~CSophiaMiddle();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

};

