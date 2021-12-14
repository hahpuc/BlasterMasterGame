#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Player.h"
#include "Bullet.h"
#include "Camera.h"
#include "TileMap.h"


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP		7

#define OBJECT_TYPE_PLAYER		0
#define OBJECT_TYPE_INTERRUPT	1
#define OBJECT_TYPE_BULLET		2
#define OBJECT_TYPE_BALLBOT		3
#define OBJECT_TYPE_BRICK		4
#define OBJECT_TYPE_STUKA		5
#define OBJECT_TYPE_EYELET		6

#define OBJECT_TYPE_PORTAL		50

#define MAX_SCENE_LINE 1024


class CPlayScene : public CScene
{
protected:
	CPlayer* player;					// A play scene has to have player, right? 

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> listEnemies;
	vector<LPGAMEOBJECT> createObjects;

	Map* map;

	Camera* camera;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);


public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CPlayer* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

//-----------------------------------------

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

