#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Player.h"
#include "Game.h"

#include "Portal.h"
#include "Bullet.h"
#include "Interrupt.h"
#include "PlayScence.h"
#include "Brick.h"

#include "SophiaMiddle.h"
#include "SophiaRightWheel.h"
#include "SophiaLeftWheel.h"
#include "SophiaCabin.h"
#include "SophiaGun.h"

CPlayer::CPlayer(float x, float y) : CGameObject()
{
	level = PLAYER_LEVEL_SHOPHIA;
	untouchable = 0;
	isJumping = false;
	isFireBullet = false;
	heal = 100;
	SetState(PLAYER_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

	middle = new CSophiaMiddle(this);
	rightWheel = new CSophiaRightWheel(this);
	leftWheel = new CSophiaLeftWheel(this);
	cabin = new CSophiaCabin(this);
	gun = new CSophiaGun(this);
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (vy < FALLING_VELOCITY_UPPER_LIMITATION)
		isJumping = false;
	else
		isJumping = true;

	// Calculate dx, dy 
	CGameObject::Update(dt);

	middle->Update(dt);
	rightWheel->Update(dt);
	leftWheel->Update(dt);
	cabin->Update(dt);
	gun->Update(dt);

	// Simple fall down
	vy += PLAYER_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != PLAYER_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > PLAYER_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CInterrupt*>(e->obj)) 
			{
				CInterrupt* interrupt = dynamic_cast<CInterrupt*>(e->obj);
				this->GetHeal();
				this->DecreaseHeal();
				
			} // if Goomba
			
			if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CPlayer::Render()
{
	middle->Render();
	rightWheel->Render();
	leftWheel->Render();
	cabin->Render();
	gun->Render();

	RenderBoundingBox();
}

void CPlayer::SetState(int state)
{
	CGameObject::SetState(state);

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
		// TODO: need to check if PLAYER is *current* on a platform before allowing to jump again
		vy = -PLAYER_JUMP_SPEED_Y;
		break;
	case PLAYER_STATE_IDLE:
		vx = 0;
		break;
	case PLAYER_STATE_DIE:
		vy = -PLAYER_DIE_DEFLECT_SPEED;
		break;
	}
}

void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == PLAYER_LEVEL_SHOPHIA)
	{
		right = x + PLAYER_BIG_BBOX_WIDTH;
		bottom = y + PLAYER_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + PLAYER_SMALL_BBOX_WIDTH;
		bottom = y + PLAYER_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CPlayer::Reset()
{
	this->IncreaseHeal();
	SetState(PLAYER_STATE_IDLE);
	SetLevel(PLAYER_LEVEL_SHOPHIA);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

CGameObject* CPlayer::NewBullet() {

	int ani_set_id = BULLET_ANI_SETS_ID;
	float transX = 0, transY = 0;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = new CBullet(this->nx, this);

	if (this->GetState() == PLAYER_STATE_HEAD_UP) {
		obj->SetState(BULLET_STATE_HEAD_UP);

		transX = 16.0;
		transY = -32.0;
	}
	else {
		obj->SetState(BULLET_STATE_NORMAL);

		transX = nx * PLAYER_BIG_BBOX_WIDTH / 2;
		transY = 0;
	}

	obj->type = OBJECT_TYPE_BULLET;
	obj->SetPosition(this->x + transX, this->y + transY);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	obj->SetAnimationSet(ani_set);

	return obj;
}