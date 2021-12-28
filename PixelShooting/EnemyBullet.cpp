#include "Core.h"

EnemyBullet::EnemyBullet(D3DXVECTOR2 pos, float angle, float speed, float angleRotate, D3DXCOLOR color)
	:IBullet(pos, angle, speed, L"EnemyBullet", angleRotate)
{
	ri.r = color.r * 255;
	ri.g = color.g * 255;
	ri.b = color.b * 255;

	ri.rotate = -angle;
}

void EnemyBullet::Update(float deltaTime)
{
	ri.rotate = -D3DXToDegree(radian);

	// 유도 만들기
	IBullet::Update(deltaTime);
}

void EnemyBullet::Render()
{
	IBullet::Render();
}

void EnemyBullet::OnCollision2D(Collider2D&)
{
}
