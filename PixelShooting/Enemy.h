#pragma once
class Enemy : public Object
{
public:
	bool isHit = false;
	float hitTime = 0.0f;
	float bulletTime = 0.0f;
	int hp = 3;

	Sprite spr2D;
	Sprite::RenderInfo ri;

	Enemy(D3DXVECTOR2 pos, int enemyIndex = 1);

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision2D(Collider2D& _collider2D) override;

	void Hit(float deltaTime);
	void OnDestroy();
};

