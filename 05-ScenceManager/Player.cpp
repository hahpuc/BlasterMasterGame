#include "Player.h"


Player::Player(float x, float y, float vx) : Entity(x, y) {
	this->vx = vx;
}

void Player::Update(DWORD dt) {
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - PLAYER_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - PLAYER_WIDTH)
		{
			x = (float)(BackBufferWidth - PLAYER_WIDTH);
		}
	}
}

void Player::Render() {
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx > 0) ani = CAnimations::GetInstance()->Get(500);
	else ani = CAnimations::GetInstance()->Get(501);

	ani->Render(x, y);
}