#pragma once
#include "GameObject.h"
#include "Jason.h"

#define RAINBOW_BULLET_BBOX_WIDTH		8
#define RAINBOW_BULLET_BBOX_HEIGHT		10

#define RAINBOW_BULLET_ANI_FIRE			0 
#define RAINBOW_BULLET_ANI_FINISH		1

#define RAINBOW_BULLET_ANI_SETS_ID		3

#define RAINBOW_BULLET_SPEED			0.25f
#define RAINBOW_BULLET_SPEED_WAVE		0.7f
#define RAINBOW_BULLET_GRAVITY			0.001f

#define RAINBOW_BULLET_STATE_FIRE		100
#define RAINBOW_BULLET_STATE_FINISH		500

#define PI							3.14


class CRainbowBullet : public CGameObject
{
	int count;
	bool nxORny;

public:

	CJason* parent;

	CRainbowBullet(int nx, int ny, CJason* parent);
	void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};