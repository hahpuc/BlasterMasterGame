#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Animation.h"


class Entity {

protected:
	float x;
	float y;

	float vx; 
	float vy;

	int nx;

	int state;

	static vector<LPANIMATION> animations;

public:
	Entity();
	~Entity();

	// ----- RENDER 
	static void AddAnimation(int aniId);
	void Update(DWORD dt); 
	void Render();

	// ------ SET/GET 
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

};