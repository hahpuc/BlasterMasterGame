#include "GX680.h"
#include "Game.h"
#include "Utils.h"
#include "Brick.h"

CGX680::CGX680()
{

}

CGX680::CGX680(float x, float y, CJason* player) {
	this->x = x;
	this->y = y;
	this->player = player;

	vx = GX680_SPEED;
	isDying = 0;
	isAddedItem = 0;
	SetState(GX680_STATE_STANDING);
}

void CGX680::Render()
{
	if (isFinish && isDying) return;

	int ani = GX680_ANI_STANDING;

	if (this->GetState() == GX680_STATE_WALKING)
		ani = GX680_ANI_WALKING;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CGX680::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isFinish) return;

	l = x;
	t = y;
	r = x + GX680_BBOX_WIDTH;
	b = y + GX680_BBOX_HEIGHT;
}

void CGX680::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGame* game = CGame::GetInstance();
	float camx;
	float camy;
	float screenWidth = float(game->GetScreenWidth());
	float screenHeight = float(game->GetScreenHeight());
	game->GetCamPos(camx, camy);


	if (isFinish && isDying && !isAddedItem) {
		this->AddItemWhenDie();
		isAddedItem = 1;
		return;
	}

	this->player->GetPosition(pX, pY);

	if ((abs(x - pX) < GX680_RANGE || abs(y - pY) < GX680_RANGE) && state == GX680_STATE_STANDING)
	{
		SetState(GX680_STATE_WALKING);
	}

	if (state == GX680_DYING_TIME) {
		if (GetTickCount64() - die_start > GX680_DYING_TIME) {
			die_start = 0;
			isDying = 1;
		}
	}	

	if (state == GX680_STATE_WALKING)
	{
		if (abs(x - pX) > GX680_RANGE || abs(y - pY) > GX680_RANGE)
		{
			SetState(GX680_STATE_STANDING);
		}
	}

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != GX680_STATE_DIE)
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

		for (int i = 0; i < coEventsResult.size(); ++i) {
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))				// object is Brick
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx != 0 && e->ny == 0)
				{
					vx = GX680_SPEED * e->nx;
				}
			}
			else
			if (dynamic_cast<CJason*>(e->obj))
			{
				CJason* jason = dynamic_cast<CJason*>(e->obj);
				jason->DecreaseHeal(10);
			}
		}
	}
}

void CGX680::AddItemWhenDie() {
	LPSCENE currentScene = CGame::GetInstance()->GetCurrentScene();
	currentScene->isAddedItem = false;
	currentScene->AddItemAt(this->x, this->y);
}

void CGX680::SetState(int state) {
	CGameObject::SetState(state);

	switch (state)
	{
	case GX680_STATE_DIE:
		vx = 0; vy = 0;
		isFinish = 1;
		StartDying();
		break;
	case GX680_STATE_STANDING:
		vx = 0;
		vy = 0;
		break;

	case GX680_STATE_WALKING:
		if ((pX - x) > 0) vx = GX680_SPEED;
		else 
		if ((pX - x) < 0) vx = -GX680_SPEED;

		if ((pY - y) > 0) vy = GX680_SPEED;
		else 
		if ((pY - y) < 0) vy = -GX680_SPEED;
		break;

	default:
		break;
	}
}

CGX680::~CGX680()
{

}