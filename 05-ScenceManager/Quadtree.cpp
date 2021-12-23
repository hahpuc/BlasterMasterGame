#include"Quadtree.h"


Quadtree::Quadtree()
{
	level = 0;
	x = 0.0f;
	y = 0.0f;
	width = 0.0f;
	height = 0.0f;
}
Quadtree::Quadtree(int level, float x, float y, float w, float h)
{
	this->level = level;
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}
Quadtree::~Quadtree()
{

}
void Quadtree::Clear()
{
	if (Nodes.size() != 0)
	{
		for (auto value : Nodes)
		{
			value->Clear();
			delete value;
		}
	}
	ObjectList.clear();
}

bool Quadtree::IsContain(CGameObject* obj)
{
	if (obj == NULL)
		return false;
	int type = obj->GetType();
	float l, t, r, b;
	obj->GetBoundingBox(l, t, r, b);

	return CGame::GetInstance()->AABBCheck(l, t, r, b, this->x, this->y, this->x + this->width, this->y + this->height);
}
void Quadtree::Split()
{
	Nodes.push_back(new Quadtree(level + 1, x, y, width / 2, height / 2));
	Nodes.push_back(new Quadtree(level + 1, x + width / 2, y, width / 2, height / 2));
	Nodes.push_back(new Quadtree(level + 1, x, y + height / 2, width / 2, height / 2));
	Nodes.push_back(new Quadtree(level + 1, x + width / 2, y + height / 2, width / 2, height / 2));
	DebugOut(L"New Nodes level %i has been created with %i\n", level + 1, Nodes.size());

}
void Quadtree::Insert(CGameObject* obj)
{
	if (Nodes.size() != 0)
	{
		if (Nodes[0]->IsContain(obj))
			Nodes[0]->Insert(obj);
		if (Nodes[1]->IsContain(obj))
			Nodes[1]->Insert(obj);
		if (Nodes[2]->IsContain(obj))
			Nodes[2]->Insert(obj);
		if (Nodes[3]->IsContain(obj))
			Nodes[3]->Insert(obj);
		return;
	}
	if (this->IsContain(obj) == true && obj->GetIsInserted() == false)
	{
		ObjectList.push_back(obj);
		obj->SetInsertToQuadtree(true);
	}

	if (ObjectList.size() > MAX_OBJECT_IN_REGION && level < MAX_LEVEL)
	{
		Split();
		while (!ObjectList.empty())
		{
			if (Nodes[0]->IsContain(ObjectList.back()))
			{
				ObjectList.back()->SetInsertToQuadtree(false);
				Nodes[0]->Insert(ObjectList.back());
			}

			if (Nodes[1]->IsContain(ObjectList.back()))
			{
				ObjectList.back()->SetInsertToQuadtree(false);
				Nodes[1]->Insert(ObjectList.back());
			}

			if (Nodes[2]->IsContain(ObjectList.back()))
			{
				ObjectList.back()->SetInsertToQuadtree(false);
				Nodes[2]->Insert(ObjectList.back());
			}

			if (Nodes[3]->IsContain(ObjectList.back()))
			{
				ObjectList.back()->SetInsertToQuadtree(false);
				Nodes[3]->Insert(ObjectList.back());
			}

			ObjectList.pop_back();
		}
	}

}
bool Quadtree::CheckNodeInsideCamera(Camera* camera)
{
	float cam_x, cam_y;
	camera->GetPosition(cam_x, cam_y);
	float left, top, right, bottom;
	left = cam_x;
	top = cam_y;
	right = cam_x + CGame::GetInstance()->GetScreenWidth();
	bottom = cam_y + CGame::GetInstance()->GetScreenHeight();
	return CGame::GetInstance()->AABBCheck(this->x, this->y, this->x + this->width, this->y + this->height, left, top, right, bottom);
}
void Quadtree::GetListObjectInCamera(vector<CGameObject*>& Obj, Camera* camera)
{

	if (Nodes.size() != 0)
	{
		if (Nodes[0]->CheckNodeInsideCamera(camera))
			Nodes[0]->GetListObjectInCamera(Obj, camera);
		if (Nodes[1]->CheckNodeInsideCamera(camera))
			Nodes[1]->GetListObjectInCamera(Obj, camera);
		if (Nodes[2]->CheckNodeInsideCamera(camera))
			Nodes[2]->GetListObjectInCamera(Obj, camera);
		if (Nodes[3]->CheckNodeInsideCamera(camera))
			Nodes[3]->GetListObjectInCamera(Obj, camera);
		return;
	}

	if (this->CheckNodeInsideCamera(camera))
	{
		for (auto value : ObjectList)
		{
			Obj.push_back(value);
		}
	}
	
	DebugOut(L"Number Object in camera %d: \n", Obj.size());
	/*for (auto object : Obj) {
		DebugOut(L" TYPE: %d ", object->GetType());
	}
	DebugOut(L"-------------->\n");*/
}

void Quadtree::NumberOfObjectsInNodes()
{
	if (Nodes.size() != 0)
	{
		for (auto value : Nodes)
		{
			value->NumberOfObjectsInNodes();
		}
	}
	DebugOut(L"Nodes level %i has %i objects at X = %f, Y = %f\n", level, ObjectList.size(), this->x, this->y);

	for (auto obj : ObjectList) {
		float x, y;
		obj->GetPosition(x, y);
		DebugOut(L"Obj type: %d at (%f, %f)\n", obj->GetType(), x, y);
	}

	DebugOut(L"------------------------------------------ \n");

}