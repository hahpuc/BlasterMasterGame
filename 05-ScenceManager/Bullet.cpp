
#include "Bullet.h"
#include "Game.h"
#include "Interrupt.h"
#include "Brick.h"
#include "Utils.h"
#include "BallBot.h"
#include "Eyelet.h"
#include "Stuka.h"
#include "BallCarry.h"

CBullet::CBullet(int nx, CPlayer* parent) {
	vx = BULLET_SPEED * nx;

	this->nx = nx;

	this->parent = parent;
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish)
		return;

	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float camx, camy;
	float screenHeight = game->GetScreenHeight();
	float screenWidth = game->GetScreenWidth();
	game->GetCamPos(camx, camy);


	// DELETE bullet if out of map 
	if (x < camx || x > camx + screenWidth) 
		isFinish = 1;
	if (y < camy || y > camy + screenHeight)
		isFinish = 1;

	if (isFinish)
		return;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (int i = 0; i < coEventsResult.size(); ++i) {
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CInterrupt*>(e->obj)) {   // If object is Interrupt
				isFinish = 1;
				CInterrupt* interrupt = dynamic_cast<CInterrupt*>(e->obj);
				
				interrupt->DecreaseHeal(50);
				DebugOut(L"Heal of interrupt: %d \n", interrupt->GetHeal());

				if (interrupt->GetHeal() <= 0) 
					interrupt->SetState(INTERRUPT_STATE_DIE);

			}

			if (dynamic_cast<CBallBot*>(e->obj)) {   // If object is BallBot
				isFinish = 1;
				CBallBot* ballBot = dynamic_cast<CBallBot*>(e->obj);

				/*ballBot->DecreaseHeal(50);
				DebugOut(L"Heal of ballBot: %d \n", ballBot->GetHeal());

				if (ballBot->GetHeal() <= 0)*/
					ballBot->SetState(BALLBOT_STATE_DIE);
			}

			if (dynamic_cast<CEyelet* > (e->obj)) {   // If object is Eyelet
				isFinish = 1;
				CEyelet* eyelet = dynamic_cast<CEyelet*>(e->obj);

				/*eyelet->DecreaseHeal(50);
				DebugOut(L"Heal of ballBot: %d \n", eyelet->GetHeal());

				if (eyelet->GetHeal() <= 0)*/
					eyelet->SetState(EYELET_STATE_DIE);
			}

			if (dynamic_cast<CBallCarry*> (e->obj)) {   // If object is Carry
				isFinish = 1;
				CBallCarry* ballCarray = dynamic_cast<CBallCarry*>(e->obj);

				ballCarray->DecreaseHeal(50);
				DebugOut(L"Heal of ballBot: %d \n", ballCarray->GetHeal());

				if (ballCarray->GetHeal() <= 0)
					ballCarray->SetState(BALLCARRY_STATE_DIE);
			}

			if (dynamic_cast<CStuka*> (e->obj)) {   // If object is Stuke
				isFinish = 1;
				CStuka* stuka = dynamic_cast<CStuka*>(e->obj);

				stuka->DecreaseHeal(50);
				DebugOut(L"Heal of ballBot: %d \n", stuka->GetHeal());

				if (stuka->GetHeal() <= 0)
					stuka->SetState(STUKA_STATE_DIE);
			}

			else if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				isFinish = 1;
			}
		}
	}
}

void CBullet::Render()
{
	if (isFinish)
		return;

	int ani = BULLET_ANI_RIGHT_LV3;

	if (parent->GetState() == PLAYER_STATE_HEAD_UP)
		ani = BULLET_ANI_TOP_LV3;
	else {
		if (vx > 0) ani = BULLET_ANI_RIGHT_LV3;
		else if (vx <= 0) ani = BULLET_ANI_LEFT_LV3;
	}	

	animation_set->at(ani)->Render(round(x), round(y));
	//RenderBoundingBox(); 
}

void CBullet::SetState(int state) {
	CGameObject::SetState(state); 

	switch (state)
	{
	case BULLET_STATE_NORMAL: 
		vx = BULLET_SPEED * nx;
		vy = 0;
		break;

	case BULLET_STATE_HEAD_UP:
		vy = -BULLET_SPEED;
		vx = 0;
		break;

	default:
		break;
	}
}