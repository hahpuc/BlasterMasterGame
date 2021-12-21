#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Jason.h"
#include "Game.h"
#include "DungeonPlayScene.h"
#include "RainbowBullet.h"

#include "Portal.h"
#include "Brick.h"


CJason::CJason(float x, float y) : CGameObject()
{
	untouchable = 0;

	isFireBullet = false;
	heal = 100;
	SetState(JASON_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

}

void CJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != JASON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > JASON_UNTOUCHABLE_TIME)
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

			// if Goomba
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

void CJason::Render()
{
	//this->animation_set->at(ani)->Render(partX + transX, partY + transY);
	int ani = JASON_ANI_IDLE_TOP_DOWN;

	if (this->GetState() == JASON_STATE_IDLE) {
		if (nx > 0)
			ani = JASON_ANI_IDLE_RIGHT;
		else
			ani = JASON_ANI_IDLE_LEFT;
	}
	else
	if (this->GetState() == JASON_STATE_WALKING_RIGHT)
		ani = JASON_ANI_WALKING_RIGHT;
	else
	if (this->GetState() == JASON_STATE_WALKING_LEFT)
		ani = JASON_ANI_WALKING_LEFT;
	else
	if (this->GetState() == JASON_STATE_WALKING_TOPDOWN)
		ani = JASON_ANI_WALKING_TOP_DOWN;
	else
	if (this->GetState() == JASON_STATE_WALKING_TOPUP)
		ani = JASON_ANI_WALKING_TOP_UP;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CJason::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case JASON_STATE_WALKING_RIGHT:
		vx = JASON_WALKING_SPEED;
		vy = 0;
		nx = 1;
		break;
	case JASON_STATE_WALKING_LEFT:
		vx = -JASON_WALKING_SPEED;
		vy = 0;
		nx = -1;
		break;
	case JASON_STATE_WALKING_TOPDOWN:
		// TODO: need to check if PLAYER is *current* on a platform before allowing to jump again
		vy = JASON_WALKING_SPEED;
		nx = 1;
		vx = 0;
		break;
	case JASON_STATE_WALKING_TOPUP:
		vy = -JASON_WALKING_SPEED;
		nx = -1;
		vx = 0;
		break;

	case JASON_STATE_IDLE: 
		vy = 0;
		vx = 0;
		break;

	case JASON_STATE_DIE:
		//vy = -0;
		break;
	}
}

void CJason::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;	
	right = x + JASON_BBOX_WIDTH;
	bottom = y + JASON_BBOX_HEIGHT;
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CJason::Reset()
{
	this->IncreaseHeal();
	SetState(JASON_ANI_IDLE_TOP_DOWN);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

CGameObject* CJason::NewBullet() {

	int ani_set_id = RAINBOW_BULLET_ANI_SETS_ID;
	float transX = 0, transY = 0;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = new CRainbowBullet(this->nx, this);

	if (this->GetState() == JASON_STATE_WALKING_LEFT) {
		obj->SetState(RAINBOW_BULLET_STATE_LEFT);
	}
	else 
	if (this->GetState() == JASON_STATE_WALKING_RIGHT) {
		obj->SetState(RAINBOW_BULLET_STATE_RIGHT);
	}
	else 
	if (this->GetState() == JASON_STATE_WALKING_TOPDOWN) {
		obj->SetState(RAINBOW_BULLET_STATE_TOP_DOWN);
	}
	else 
	if (this->GetState() == JASON_STATE_WALKING_TOPUP) {
		obj->SetState(RAINBOW_BULLET_STATE_TOP_UP);
	}

	
	obj->type = OBJECT_TYPE_BULLET;
	obj->SetPosition(this->x + transX, this->y + transY);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	obj->SetAnimationSet(ani_set);

	return obj;
}