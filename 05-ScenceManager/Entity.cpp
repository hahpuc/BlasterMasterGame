#include "Entity.h"
#include <vector>


vector<LPANIMATION> Entity::animations;

Entity::Entity() {
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

Entity::~Entity() {}

void Entity::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void Entity::Render() {}


void Entity::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}
