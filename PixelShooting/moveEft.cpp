#include "Core.h"

MoveEft::MoveEft(D3DXVECTOR2 pos, D3DXVECTOR2 scale, Color color, float rotate)
	:IEffect(pos)
{
	spr2D.LoadAll(L"Assets/Sprites/Pixel.png");
	ri.scale = scale;
	ri.rotate = rotate;

	ri.a = color.a;
	ri.r = color.r;
	ri.g = color.g;
	ri.b = color.b;
	
	layer = -1;
}

void MoveEft::Update(float deltaTime)
{
	ri.scale -= ri.scale * 2 *  deltaTime;
	IEffect::Update(deltaTime);
}

void MoveEft::Render()
{
	IEffect::Render();
}
