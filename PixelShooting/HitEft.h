#pragma once
class HitEft : public IEffect
{
public:
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	float speed = 0.0f;

	HitEft(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed, Color color, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1));

	virtual void Update(float deltaTime);
	virtual void Render();
};

