#pragma once
class EnemyBullet : public IBullet
{
public:
	EnemyBullet(D3DXVECTOR2 pos,float angle, float speed = 700, float angleRotate = 0.0f, D3DXCOLOR color = 0xffff0000);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision2D(Collider2D& _collider2D) override;
};

