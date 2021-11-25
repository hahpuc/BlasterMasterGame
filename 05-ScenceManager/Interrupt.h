
#pragma once

#include "GameObject.h"


#define INTERRUPT_BBOX_WIDTH	21
#define INTERRUPT_BBOX_HEIGHT	17

class CInterrupt : public CGameObject {
public:

	CInterrupt();
	CInterrupt(float x, float y);
	~CInterrupt();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


