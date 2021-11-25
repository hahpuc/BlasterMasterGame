#include "Interrupt.h"

CInterrupt::CInterrupt()
{

}

CInterrupt::CInterrupt(float x, float y) {
	this->x = x;
	this->y = y;
}

void CInterrupt::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CInterrupt::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + INTERRUPT_BBOX_WIDTH;
	b = y + INTERRUPT_BBOX_HEIGHT;
}
CInterrupt::~CInterrupt()
{

}