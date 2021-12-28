#pragma once

class BulletEft : public IEffect
{
public:
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	float speed = 0.0f;

public:
	BulletEft(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

