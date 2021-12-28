#include "Core.h"

Bullet::Bullet(D3DXVECTOR2 pos, float angle, float speed)
	: IBullet(pos, angle, speed, L"PlayerBullet")
{
	ri.r = ri.b = 0;
}

void Bullet::Update(float deltaTime)
{
	IBullet::Update(deltaTime);
}

void Bullet::Render()
{
	IBullet::Render();
}

void Bullet::OnCollision2D(Collider2D& _collider2D)
{
	if (_collider2D.tag == L"Enemy" || _collider2D.tag == L"Boss")
		destroy = true;
}
