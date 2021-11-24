#include "Camera.h"
Camera::Camera()
{
	cam_x = 0.0f;
	cam_y = 0.0f;
	dt = 0;
	player = NULL;
}
void Camera::Update(DWORD time)
{
	if (player == NULL)
		return;

	float cx, cy;
	player->GetPosition(cx, cy);
	cx -= (float)CGame::GetInstance()->GetScreenWidth() / 2;
	cy -= (float)CGame::GetInstance()->GetScreenHeight() / 2;

	CGame::GetInstance()->SetCamPos(round(cx), round(cy));
}
Camera::~Camera()
{

}