#pragma once
#include "Utils.h"
#include "GameObject.h"
#include "Camera.h"
#include "Player.h"

#define BOUNDRRY_X_MAX 1792.0f

#define HUB_ANI_100_point	    		9
#define HUB_ANI_90_POINT				8
#define HUB_ANI_80_POINT				7
#define HUB_ANI_70_POINT				6
#define HUB_ANI_60_POINT				5
#define HUB_ANI_50_POINT				4
#define HUB_ANI_40_POINT				3
#define HUB_ANI_30_POINT				2
#define HUB_ANI_20_POINT				1
#define HUB_ANI_10_POINT				0


#define HUB_ANI_SETS_ID					40

class HUB: CGameObject
{
private:

	DWORD dt;
	Camera* camera;
	CPlayer* player;
public:
	HUB();
	~HUB();

	void SetCamera(Camera* camera) { this->camera = camera; }
	void SetPlayer(CPlayer* player) { this->player = player; }

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void Update(DWORD dt);

	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};

};
