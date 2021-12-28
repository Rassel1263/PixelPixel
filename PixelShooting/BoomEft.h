#pragma once
class BoomEft : public Object
{
public:
	Sprite spr2D;
	Sprite::RenderInfo ri;

	BoomEft(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime);
	virtual void Render();
};

