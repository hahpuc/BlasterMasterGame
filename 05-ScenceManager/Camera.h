#pragma once
#include "Utils.h"
#include "Game.h"
#include "Player.h"
#include "GameObject.h"

#define BOUNDRRY_X_MAX 1792.0f

class Camera
{
private:
	float cam_x;
	float cam_y;


	DWORD dt;
	CGameObject* player;
public:
	Camera();
	~Camera();
	void SetPlayer(CGameObject* player) { this->player = player; }
	void SetPosition(float x, float y) { this->cam_x = x, this->cam_y = y; }
	void GetPosition(float& x, float& y) { x = this->cam_x; y = this->cam_y; }
	void Update(DWORD dt);
};
