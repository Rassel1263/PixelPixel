#pragma once

struct Color
{
	float a = 0.0f;
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
};

class IEffect : public Object
{
public:
	float visibleTime = 0.0f, visibleMaxTime = 0.0f;

	Sprite spr2D;
	Sprite::RenderInfo ri;

	IEffect(D3DXVECTOR2 pos, float visibleMaxTime = 0.3f);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

