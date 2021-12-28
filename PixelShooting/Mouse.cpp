#include "Core.h"

Mouse::Mouse()
{
	tag = L"Mouse";
	colliderLayer = COLLIDERLAYER::CL_PLAYER;

	Collider2D::AABB aabb;
	aabb.min = D3DXVECTOR2(-3.0f, -3.0f);
	aabb.max = D3DXVECTOR2(3.0f, 3.0f);

	bodies.push_back(Collider2D(this, tag, nullptr, &aabb, nullptr));
}

void Mouse::Update(float deltaTime)
{
	pos = Input::GetInstance().GetWorldCursorPos();

	Object::Update(deltaTime);
}

void Mouse::Render()
{
}
