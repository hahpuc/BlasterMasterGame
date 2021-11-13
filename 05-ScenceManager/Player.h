#pragma once

#include "Entity.h"

#define PLAYER_WALKING_SPEED		0.1f
#define PLAYER_JUMP_SPEED_Y			0.5f
#define PLAYER_GRAVITY				0.1f

#define PLAYER_STATE_IDLE			0
#define PLAYER_STATE_WALKING_RIGHT	100
#define PLAYER_STATE_WALKING_LEFT	200
#define PLAYER_STATE_JUMP			300

#define PLAYER_ANI_IDLE_RIGHT		0
#define PLAYER_ANI_IDLE_LEFT		1
#define PLAYER_ANI_WALKING_RIGHT	2
#define PLAYER_ANI_WALKING_LEFT		3

class Player : public Entity {

public: 
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

