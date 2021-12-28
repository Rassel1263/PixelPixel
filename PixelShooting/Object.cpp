#include "Core.h"

Object::~Object()
{
}

Object::Object()
{
}

void Object::Update(float)
{
}

void Object::LateUpdate(float)
{
}

void Object::FixedUpdate(float)
{
}

void Object::Render()
{

#ifdef _DEBUG
	auto& d3dInst = Direct3D::GetInstance();

	for (auto& body : bodies)
	{
		if (body.type == Collider2D::Type::kLine)
		{
			D3DXMATRIX matPos;
			D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.0f);
			d3dInst.DrawLine(body.line.p1, body.line.p2, matPos);
		}
		else if (body.type == Collider2D::Type::kAABB)
		{
			D3DXMATRIX matPos;
			D3DXMatrixTranslation(&matPos, pos.x, pos.y, 0.0f);
			D3DXVECTOR2 min = body.aabb.min;
			D3DXVECTOR2 max = body.aabb.max;

			d3dInst.DrawLine(min, D3DXVECTOR2(max.x, min.y), matPos);
			d3dInst.DrawLine(D3DXVECTOR2(max.x, min.y), max, matPos);
			d3dInst.DrawLine(max, D3DXVECTOR2(min.x, max.y), matPos);
			d3dInst.DrawLine(D3DXVECTOR2(min.x, max.y), min, matPos);
		}
	}
#endif
}

void Object::OnCollision2D(Collider2D&)
{
}

ObjectManager::ObjectManager()
{
	colliderVec = new std::vector<Object*>[CL_END];
}

ObjectManager::~ObjectManager()
{
	for (auto& object : objects)
	{
		delete object;
	}
	for (auto& addObject : addObjects)
	{
		delete addObject;
	}
	for (auto& object : uiObjects)
	{
		delete object;
	}
	for (auto& addObject : uiAddObjects)
	{
		delete addObject;
	}
}

void ObjectManager::AddObject(Object * object)
{
	addObjects.push_back(object);
}

void ObjectManager::AddUiObject(ObjectUi* object)
{
	uiAddObjects.push_back(object);
}

void ObjectManager::Update(float deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();
	uiObjects.insert(uiObjects.end(), uiAddObjects.begin(), uiAddObjects.end());
	uiAddObjects.clear();

 	std::sort(objects.begin(), objects.end(), [](const Object* lhs, const Object* rhs) { 
		return lhs->layer < rhs->layer; 
	});

	for (auto object : objects)
	{
		object->Update(deltaTime);
	}

	for (auto it = objects.begin(); it != objects.end();)
	{
		(*it)->LateUpdate(deltaTime);
		if ((*it)->destroy)
		{
			delete (*it);
			*it = NULL;
			it = objects.erase(it);
		}
		else
			++it;
	}

	for (auto object : uiObjects)
	{
		object->Update(deltaTime);
	}
}

void ObjectManager::FixedUpdate(float _fixedDeltaTime)
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if ((*it)->colliderLayer == 0) continue;
		for (auto it2 = it + 1; it2 != objects.end(); ++it2)
		{
			if ((*it2)->colliderLayer == 0) continue;	
			if ((*it)->colliderLayer == (*it2)->colliderLayer) continue;
			for (auto& body1 : (*it)->bodies)
			{
				for (auto& body2 : (*it2)->bodies)
				{
					if (IntersectCollider2D(body1, body2))
					{
						body1.object->OnCollision2D(body2);
						body2.object->OnCollision2D(body1);
					}
				}
			}
		}
	}

	for (auto object : objects)
		object->FixedUpdate(_fixedDeltaTime);
}


void ObjectManager::Render()
{
	for (auto& object : objects)
		object->Render();
}

void ObjectManager::UiRender()
{
	for (auto& uiObject : uiObjects)
		uiObject->Render();
}

ObjectUi::~ObjectUi()
{
}

void ObjectUi::Update(float)
{
}

void ObjectUi::Render()
{
}
