#pragma once
class IBullet : public Object
{
public:
	float speed = 0.0f;
	float radian = 0.0f;
	float angleRate = 0;

	Sprite spr2D;
	Sprite::RenderInfo ri;

	IBullet(D3DXVECTOR2 pos, float angle, float speed, std::wstring tag, float angleRate = 0.0f);

	virtual void Update(float deltaTime);
	virtual void Render();
};

