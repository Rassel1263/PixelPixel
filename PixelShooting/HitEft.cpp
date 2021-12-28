#include "Core.h"

HitEft::HitEft(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed, Color color, D3DXVECTOR2)
	:IEffect(pos)
{
	spr2D.LoadAll(L"Assets/Sprites/Pixel.png");
	ri.scale = D3DXVECTOR2(1.0f, 1.0f);

	ri.a = color.a;
	ri.r = color.r;
	ri.g = color.g;
	ri.b = color.b;

	this->dir = dir;
	this->speed = speed;
}

void HitEft::Update(float deltaTime)
{
	ri.scale -= ri.scale * 7 * deltaTime;
	pos += dir * speed * deltaTime;

	IEffect::Update(deltaTime);
}

void HitEft::Render()
{
	IEffect::Render();
}
