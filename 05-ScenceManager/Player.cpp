#include "Player.h"

void Player::Update(DWORD dt)
{
	Entity::Update(dt);

	// simple fall down
	vy += PLAYER_GRAVITY;
	if (y > 100)
	{
		vy = 0; y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}

void Player::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx > 0) ani = PLAYER_ANI_IDLE_RIGHT;
		else ani = PLAYER_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = PLAYER_ANI_WALKING_RIGHT;
	else ani = PLAYER_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void Player::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case PLAYER_STATE_WALKING_RIGHT:
		vx = PLAYER_WALKING_SPEED;
		nx = 1;
		break;
	case PLAYER_STATE_WALKING_LEFT:
		vx = -PLAYER_WALKING_SPEED;
		nx = -1;
		break;
	case PLAYER_STATE_JUMP:
		if (y == 100)
			vy = -PLAYER_JUMP_SPEED_Y;

	case PLAYER_STATE_IDLE:
		vx = 0;
		break;
	}
}

