#include <Windows.h>
#include <d3dx9.h>
#include <vector>


class Entity {

protected:
	float x;
	float y;

public:
	Entity(float x, float y);

	void setPosition(float x, float y) {
		this -> x = x;
		this -> y = y;
	}

	float getX() { return x; }
	float getY() { return y; }

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;


};