#pragma once
#include "GameObject.h"

#define WALLMAP_ANI_SETS_ID		7



class CWallMap : public CGameObject
{
	int ani_image;

private:
public:
	CWallMap();
	CWallMap(float x, float y, int ani_image);
	~CWallMap();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};