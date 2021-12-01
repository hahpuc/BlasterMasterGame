#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH		24
#define BULLET_BBOX_HEIGHT		7

#define BULLET_ANI_RIGHT_LV2	0 
#define BULLET_ANI_TOP_LV2		1
#define BULLET_ANI_RIGHT_LV3	2
#define BULLET_ANI_TOP_LV3		3
#define BULLET_ANI_LEFT_LV2		4
#define BULLET_ANI_LEFT_LV3		5

#define BULLET_ANI_SETS_ID		24

#define BULLET_SPEED			0.25f
#define BULLET_GRAVITY			0.001f

#define BULLET_STATE_NORMAL		100



class CBullet : public CGameObject
{


public:
	CBullet(int nx);
	void SetState(int state);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};