#pragma once

class Boss : public Object
{
public:
	bool isHit = false;
	float hitTime = 0.0f;
	int hp = 150;

	//-------------∆–≈œ---------------
	float pattenTime = 0.0f;
	float rotate = 0;
	float bulletTime = 0.2f;
	float bulletTimer = 0.0f;
	float bulletSpd = 100;
	float restTime = 3.0f;
	float restTimer = 0.0f;
	//---------------------------------

	Sprite spr2D;
	Sprite::RenderInfo ri;

	std::vector<EnemyBullet*> bulletVec;
	std::vector<D3DXVECTOR2> bulletDis;

	int nowPatten = 1;
	int pastPatten = 0;

	bool fillBullet = false;

	Boss();
	
	virtual void Update(float deltaTime);
	virtual void OnCollision2D(Collider2D& _colider2D);
	virtual void Render();


	void SwirlPatten(float deltaTime, float rotateRate);
	void FlowerPatten(float deltaTime);
	void CirclePatten(float deltaTime);

	void Attack(int BulletCreate, float speed, float angleRate, int rotateDir, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	void Hit(float deltaTime);
};

