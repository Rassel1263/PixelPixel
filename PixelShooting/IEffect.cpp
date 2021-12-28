#include "Core.h"

IEffect::IEffect(D3DXVECTOR2 pos, float visibleMaxTime)
{
	this->pos = pos;
	this->visibleMaxTime = visibleMaxTime;
}

void IEffect::Update(float deltaTime)
{
	if (visibleTime > visibleMaxTime)
		destroy = true;

	if(ri.a >= 0)
		ri.a -= deltaTime * 500;

	visibleTime += deltaTime;

	Object::Update(deltaTime);
}

void IEffect::Render()
{
	ri.pos = pos;
	spr2D.Render(ri);
	Object::Render();
}
