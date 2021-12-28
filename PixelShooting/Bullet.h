#pragma once

class Bullet : public IBullet
{
public:
	Bullet(D3DXVECTOR2 pos, float angle, float speed = 700);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision2D(Collider2D& _collider2D) override;
};

