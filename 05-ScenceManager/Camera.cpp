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

	cam_x = cx;
	cam_y = cy;

	if (cam_x >= BOUNDRRY_X_MAX - (float)CGame::GetInstance()->GetScreenWidth())
		cam_x = BOUNDRRY_X_MAX - (float)CGame::GetInstance()->GetScreenWidth();

	CGame::GetInstance()->SetCamPos(round(cam_x), round(cam_y));
}
Camera::~Camera()
{

}