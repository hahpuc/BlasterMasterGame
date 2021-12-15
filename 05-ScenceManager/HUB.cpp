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

	switch (player->GetHeal())
	{
	case 100:
		ani = HUB_ANI_100_point;
		break;
	case 90:
		ani = HUB_ANI_90_POINT;
		break;

	case 80:
		ani = HUB_ANI_80_POINT;
		break;

	case 70:
		ani = HUB_ANI_70_POINT;
		break;

	case 60:
		ani = HUB_ANI_60_POINT;
		break;

	case 50:
		ani = HUB_ANI_50_POINT;
		break;

	case 40:
		ani = HUB_ANI_40_POINT;
		break;

	case 30:
		ani = HUB_ANI_30_POINT;
		break;

	case 20:
		ani = HUB_ANI_20_POINT;
		break;

	case 10:
		ani = HUB_ANI_10_POINT;
		break;

	default:
		break;
	}

	this->animation_set->at(ani)->Render(this->x, this->y);
}