#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH		24
#define BULLET_BBOX_HEIGHT		7

#define BULLET_ANI_RIGHT_LV2	0 
#define BULLET_ANI_TOP_LV2		1
#define BULLET_ANI_RIGHT_LV3	2
#define BULLET_ANI_TOP_LV3		3


class CBullet : public CGameObject
{

public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};