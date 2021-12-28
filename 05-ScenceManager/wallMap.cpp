#include "wallMap.h"

CWallMap::CWallMap()
{

}
CWallMap::CWallMap(float x, float y, int ani_image)
{
	this->x = x;
	this->y = y;
	this->ani_image = ani_image;
}
void CWallMap::Render()
{
	animation_set->at(ani_image)->Render(x, y);
	//RenderBoundingBox();
}

void CWallMap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*l = x;
	t = y;
	r = x + width;
	b = y + height;*/
}
CWallMap::~CWallMap()
{

}