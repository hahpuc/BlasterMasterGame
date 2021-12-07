#pragma once
#include "GameObject.h"

#define PLAYER_ANI_MIDDLE			3

class CSophiaMiddle : public CGameObject {
public:


public:
	CSophiaMiddle();
	~CSophiaMiddle();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

};

