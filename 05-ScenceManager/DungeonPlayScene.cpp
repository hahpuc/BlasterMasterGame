#include <iostream>
#include <fstream>

#include "DungeonPlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "GX680.h"
#include "GX680S.h"
#include "LaserGuard.h"
#include "wallMap.h"
#include "ItemHeal.h"

using namespace std;

CDungeonPlayScene::CDungeonPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CDungeonPlaySceneKeyHandler(this);
	player = NULL;
	camera = NULL;
	map = NULL;
	quadtree = NULL;

	isAddedItem = true;
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/



void CDungeonPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CDungeonPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CDungeonPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CDungeonPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CDungeonPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	int ani_image = 0;
	if (tokens.size() == 5) 
		ani_image = atoi(tokens[4].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_PLAYER:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CJason(x, y);
		player = (CJason*)obj;
		player->type = OBJECT_TYPE_PLAYER;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_BRICK:
	{
		int w = atoi(tokens[4].c_str());
		int h = atoi(tokens[5].c_str());
		obj = new CBrick(x, y, w, h);
		obj->type = OBJECT_TYPE_BRICK;

		objects.push_back((CBrick*)obj);

		DebugOut(L"[INFO] BRICK at %f, %f object created!\n", x, y);

		break;
	}
	case OBJECT_TYPE_GX680:
	{
		obj = new CGX680(x, y, player);
		obj->type = OBJECT_TYPE_GX680;
		listEnemies.push_back((CGX680*)obj);
		break;
	}

	case OBJECT_TYPE_GX680S:
	{
		obj = new CGX680S(x, y, player);
		obj->type = OBJECT_TYPE_GX680S;
		listEnemies.push_back((CGX680S*)obj);
		break;
	}

	case OBJECT_TYPE_WALL_OF_MAP: 
	{
		obj = new CWallMap(x, y, ani_image);
		obj->type = OBJECT_TYPE_WALL_OF_MAP;
		wallMap.push_back((CWallMap*)obj);
		break;
	}


	case OBJECT_TYPE_LASER_GUARD:
	{
		obj = new CLaserGuard(x, y);
		obj->type = OBJECT_TYPE_LASER_GUARD;
		listEnemies.push_back((CLaserGuard*)obj);
		break;
	}
	

	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		obj->type = OBJECT_TYPE_PORTAL;
		objects.push_back((CBrick*)obj);

	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);

	quadtree->Insert(obj);
}

void CDungeonPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 7) return;
	int idTileSet = atoi(tokens[0].c_str());
	int totalRowsTileSet = atoi(tokens[1].c_str());
	int totalColumnsTileSet = atoi(tokens[2].c_str());
	int totalRowsMap = atoi(tokens[3].c_str());
	int totalColumnsMap = atoi(tokens[4].c_str());
	int totalTiles = atoi(tokens[5].c_str());
	wstring file_path = ToWSTR(tokens[6]);

	map = new Map(idTileSet, totalRowsTileSet, totalColumnsTileSet, totalRowsMap, totalColumnsMap, totalTiles);
	map->LoadMap(file_path.c_str());
	map->ExtractTileFromTileSet();

	quadtree = new Quadtree(0.0f, 0.0f, 0.0f, 512, 2023);
}

void CDungeonPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;

		}
	}

	f.close();

	//CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	camera = new Camera();
	camera->SetPlayer(player);

	quadtree->NumberOfObjectsInNodes();


	hub = new HUB();
	hub->SetCamera(camera);
	hub->SetJason(player);
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CDungeonPlayScene::AddItemAt(float x, float y) {
	
	DebugOut(L"Add item at DUGEON %f, %f \n", x, y);

	this->itemX = x;
	this->itemY = y;	
}

void CDungeonPlayScene::Update(DWORD dt)
{
	// Delete CreateObjects
	for (int i = 0; i < createObjects.size(); ++i) {
		if (createObjects[i]->isFinish == 1)
			createObjects.erase(createObjects.begin() + i);
	}

	// Draw Fire Bullet

	if (player->BeingFireBullet()) {
		createObjects.push_back(player->NewBullet());
		player->CancelFireBullet();
	}

	if (!isAddedItem) {
		CGameObject* obj = NULL;
		obj = new CItemHeal(itemX, itemY);
		obj->type = OBJECT_TYPE_ITEMS_HEAL;

		items.push_back((CItemHeal*)obj);

		isAddedItem = true;
	}


	// Push objects that can collide
	vector<LPGAMEOBJECT> coObjects;

	if (quadtree != NULL)
		quadtree->GetListObjectInCamera(coObjects, camera);

	for (int i = 0; i < objects.size(); i++)
		coObjects.push_back(objects[i]);

	for (int i = 0; i < listEnemies.size(); i++)
		coObjects.push_back(listEnemies[i]);

	for (int i = 0; i < createObjects.size(); i++)
		coObjects.push_back(createObjects[i]);

	for (int i = 0; i < items.size(); i++)
		coObjects.push_back(items[i]);


	// skip the rest if scene was already unloaded (Jason::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	for (int i = 0; i < createObjects.size(); ++i)
		createObjects[i]->Update(dt, &coObjects);

	for (int i = 0; i < listEnemies.size(); ++i)
		listEnemies[i]->Update(dt, &coObjects);

	for (int i = 0; i < objects.size(); ++i)
		objects[i]->Update(dt, &coObjects);

	// SET UP camera;
	float posx, posy;
	player->GetPosition(posx, posy);

	//DebugOut(L"Pos x: %f, pos y: %f \n", posx, posy);

	// Update camera to follow Jason
	camera->Update(dt);

	// Update Hub to follow camera
	hub->Update(dt);

	// Update Objects
	player->Update(dt, &coObjects);

	coObjects.clear();
}

void CDungeonPlayScene::Render()
{
	if (map)
	{
		this->map->Render();
	}

	player->Render();

	for (int i = 0; i < wallMap.size(); ++i)
		wallMap[i]->Render();

	for (int i = 0; i < createObjects.size(); ++i)
		createObjects[i]->Render();

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	for (int i = 0; i < listEnemies.size(); ++i)
		listEnemies[i]->Render();

	for (int i = 0; i < items.size(); ++i)
		items[i]->Render();

	hub->Render();
}

/*
	Unload current scene
*/
void CDungeonPlayScene::Unload()
{

	for (int i = 0; i < createObjects.size(); ++i)
		delete objects[i];

	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	for (int i = 0; i < listEnemies.size(); ++i)
		delete listEnemies[i];

	for (int i = 0; i < wallMap.size(); ++i)
		delete wallMap[i];

	for (int i = 0; i < items.size(); ++i)
		delete items[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CDungeonPlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CJason* player = ((CDungeonPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_Z:
		player->FireBullet();
		break;
	case DIK_A:
		player->Reset();
		break;
	}
}

void CDungeonPlaySceneKeyHandler::OnKeyUp(int KeyCode) {
	CJason* player = ((CDungeonPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_Z:
		player->CancelFireBullet();
		break;
	}
}

void CDungeonPlaySceneKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CJason* player = ((CDungeonPlayScene*)scence)->GetPlayer();

	// disable control key when player die 
	if (player->GetState() == JASON_STATE_DIE) return;

	if (game->IsKeyDown(DIK_RIGHT))
		player->SetState(JASON_STATE_WALKING_RIGHT);
	else
	if (game->IsKeyDown(DIK_LEFT))
		player->SetState(JASON_STATE_WALKING_LEFT);
	else
	if (game->IsKeyDown(DIK_UPARROW))
		player->SetState(JASON_STATE_WALKING_TOPUP);
	else
	if (game->IsKeyDown(DIK_DOWNARROW))
		player->SetState(JASON_STATE_WALKING_TOPDOWN);
	else
		player->SetState(JASON_STATE_IDLE);
}