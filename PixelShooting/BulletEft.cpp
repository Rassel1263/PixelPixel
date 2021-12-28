#include "Core.h"

BulletEft::BulletEft(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed)
	:IEffect(pos)
{
	spr2D.LoadAll(L"Assets/Sprites/moveEft.png");
	ri.scale = D3DXVECTOR2(0.7f, 0.7f);

	ri.r = ri.b = 0;

	this->dir = dir;
	this->speed = speed;
}

void BulletEft::Update(float deltaTime)
{
	pos += dir * speed * deltaTime;
	ri.scale -= ri.scale * deltaTime;

	IEffect::Update(deltaTime);
}

void BulletEft::Render()
{
	IEffect::Render();
}
