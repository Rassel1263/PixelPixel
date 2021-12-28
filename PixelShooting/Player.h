#pragma once

class Player : public Object
{
public:

	bool isDash = false;
	bool isHit = false;
	float dashTime = 0.0f, dashCoolTime = 0.1f;
	float eftTime = 0.0f;
	float exp = 0.0f;
	float angleRange = 15.0f;
	int bulletCount = 1;
	int hp = 3;
	D3DXVECTOR2 tempDir = D3DXVECTOR2(0.0f, 0.0f);

	Sprite spr2D;
	Sprite::RenderInfo ri;

	Player();
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision2D(Collider2D& _collider2D) override;

	bool Move(float deltaTime);
	void Dash(float deltaTime);
	void Shoot();
	void Hit(float deltaTime);
	void LevelUp();
};