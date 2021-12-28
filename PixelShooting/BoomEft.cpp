#include "Core.h"

BoomEft::BoomEft(D3DXVECTOR2 pos)
{
	spr2D.LoadAll(L"Assets/Sprites/Effect/No");
	ri.scale = D3DXVECTOR2(0.5f, 0.5f);
	spr2D.aniMaxTime = 0.02f;
	spr2D.aniLoop = false;
	this->pos = pos;
}

void BoomEft::Update(float deltaTime)
{
	ri.scale += ri.scale * 3 * deltaTime;

	if (spr2D.scene >= spr2D.szScene - 1)
		destroy = true;

	spr2D.Update(deltaTime);
	Object::Update(deltaTime);
}

void BoomEft::Render()
{
	ri.pos = pos;
	spr2D.Render(ri);
}
