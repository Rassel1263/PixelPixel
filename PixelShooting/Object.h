#pragma once

enum COLLIDERLAYER
{
	CL_NONE,
	CL_PLAYER,
	CL_BULLET,
	CL_ENEMY,
	CL_END,
};

class Collider2D;
class Object
{
public:

	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	int layer = 0;
	bool destroy = false;
	std::wstring tag;
	std::vector<Collider2D> bodies;
	int colliderLayer = COLLIDERLAYER::CL_NONE;

	Object();
	virtual ~Object();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void FixedUpdate(float _fixedDeltaTime);
	virtual void Render();
	virtual void OnCollision2D(Collider2D& _colider2D);
};

class ObjectUi
{
public:
	D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
	virtual ~ObjectUi();
	virtual void Update(float deltaTime);
	virtual void Render();
};

class ObjectManager
{
private:

	std::vector<ObjectUi*> uiObjects;
	std::vector<ObjectUi*> uiAddObjects;
	std::vector<Object*> objects;
	std::vector<Object*> addObjects;
	std::vector<Object*> *colliderVec;
public:
	ObjectManager();
	~ObjectManager();

	void AddObject(Object* object);
	void AddUiObject(ObjectUi* object);

	void Update(float deltaTime);
	void FixedUpdate(float _fixedDeltaTime);

	void Render();
	void UiRender();
};