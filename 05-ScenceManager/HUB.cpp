#include "HUB.h"
HUB::HUB()
{
	this->x = 0.0f;
	this->y = 0.0f;
	dt = 0;
	camera = NULL;

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(HUB_ANI_SETS_ID);
	SetAnimationSet(ani_set);
}
void HUB::Update(DWORD time)
{
	if (camera == NULL)
		return;

	float cx, cy;
	camera->GetPosition(cx, cy);

	cx += 20.0;
	cy += (float)CGame::GetInstance()->GetScreenHeight() / 2 ;
	
	this->SetPosition(cx, cy);
}
HUB::~HUB()
{

}

void HUB::Render() {

	int ani = HUB_ANI_100_point;
	this->animation_set->at(ani)->Render(this->x, this->y);
}