
#include "Bullet.h"


void CBullet::Render()
{
	animation_set->at(2)->Render(x, y);
	//RenderBoundingBox();
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}