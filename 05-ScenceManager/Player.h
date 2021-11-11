#include "Entity.h"
#include "Game.h"
#include "Animation.h"

#define PLAYER_WIDTH 14

class Player : public Entity {
protected:
	float vx;

public: 
	Player(float x, float y, float vx);

	void Update(DWORD dt);
	void Render();

};

