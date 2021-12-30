
#include "RainbowBullet.h"
#include "Game.h"
#include "Brick.h"
#include "GX680.h"
#include "GX680S.h"
#include "LaserGuard.h"
#include "ItemHeal.h"


CRainbowBullet::CRainbowBullet(int nx, int ny, CJason* parent) {
	vx = RAINBOW_BULLET_SPEED * nx;

	this->nx = nx;
	this->ny = ny;

	this->parent = parent;
}

void CRainbowBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish)
		return;

	l = x;
	t = y;
	r = x + RAINBOW_BULLET_BBOX_WIDTH;
	b = y + RAINBOW_BULLET_BBOX_HEIGHT;
}

void CRainbowBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

	if (isFinish || this->state == RAINBOW_BULLET_STATE_FINISH)
		return;

	if (count >= 180) count = 0;

	int angle = 30;

	if (state == RAINBOW_BULLET_STATE_FIRE)
	{
		switch (nxORny)
		{
		case false:

			angle = rand() % 40 + 30;
			vy = RAINBOW_BULLET_SPEED_WAVE * cos(PI + count * PI / 180 * angle);
			count = count++;
			break;
		case true:
			angle = rand() % 40 + 30;
			vx = RAINBOW_BULLET_SPEED_WAVE * cos(PI + count * PI / 180 * angle);
			count = count++;
			break;
		}
	}

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

			if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				this->SetState(RAINBOW_BULLET_STATE_FINISH);
			}

			if (dynamic_cast<CGX680*>(e->obj)) {   // If object is GX680
				CGX680* gx680 = dynamic_cast<CGX680*>(e->obj);

				gx680->DecreaseHeal(50);
				DebugOut(L"Heal of GX680: %d \n", gx680->GetHeal());

				if (gx680->GetHeal() <= 0)
					gx680->SetState(GX680_STATE_DIE);

				this->SetState(RAINBOW_BULLET_STATE_FINISH);

			}

			if (dynamic_cast<CGX680S*>(e->obj)) {   // If object is GX680S
				CGX680S* gx680s = dynamic_cast<CGX680S*>(e->obj);

				gx680s->DecreaseHeal(50);
				DebugOut(L"Heal of gx680s: %d \n", gx680s->GetHeal());

				if (gx680s->GetHeal() <= 0)
					gx680s->SetState(GX680S_STATE_DIE);

				this->SetState(RAINBOW_BULLET_STATE_FINISH);
			}

			if (dynamic_cast<CLaserGuard*>(e->obj)) {   // If object is 
				CLaserGuard* laser = dynamic_cast<CLaserGuard*>(e->obj);

				laser->DecreaseHeal(50);
				DebugOut(L"Heal of laser: %d \n", laser->GetHeal());

				if (laser->GetHeal() <= 0)
					laser->SetState(LaserGuard_STATE_DIE);

				this->SetState(RAINBOW_BULLET_STATE_FINISH);
			}

			if (dynamic_cast<CItemHeal*>(e->obj))				// object is Brick
			{
				CItemHeal* item = dynamic_cast<CItemHeal*>(e->obj);
				this->SetState(RAINBOW_BULLET_STATE_FINISH);
			}

		}
	}
}

void CRainbowBullet::Render()
{
	if (isFinish)
		return;

	int ani = RAINBOW_BULLET_ANI_FIRE;

	if (this->state == RAINBOW_BULLET_STATE_FINISH) {
		ani = RAINBOW_BULLET_ANI_FINISH;
		this->isFinish = 1;
	}

	animation_set->at(ani)->Render(round(x), round(y));
	//RenderBoundingBox(); 
}

void CRainbowBullet::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case RAINBOW_BULLET_STATE_FIRE:
		vx = nx * RAINBOW_BULLET_SPEED;
		vy = ny * RAINBOW_BULLET_SPEED;
		if (vx == 0)
		{
			vx = RAINBOW_BULLET_SPEED_WAVE * cos(PI + count * PI / 180 * 10);
			nxORny = true;
		}

		if (vy == 0)
		{
			nxORny = false;
			vy = RAINBOW_BULLET_SPEED_WAVE * cos(PI + count * PI / 180 * 10);
		}
		break;

	case RAINBOW_BULLET_STATE_FINISH:
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}
}