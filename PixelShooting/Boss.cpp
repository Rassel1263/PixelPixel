#include "Core.h"
#include <ctime>

Boss::Boss()
{
	spr2D.LoadAll(L"Assets/Sprites/Boss.png");

	tag = L"Boss";
	// 콜라이더 생성
	Collider2D::Circle circle;
	circle.radius = 30.0f;
	bodies.push_back(Collider2D(this, tag, nullptr, nullptr, &circle));
	colliderLayer = COLLIDERLAYER::CL_ENEMY;

	ri.scale = { 0.5f, 0.5f };

	// 패턴 기본 설정
	bulletTime = 0.2f;
	nowPatten = 4;
	pastPatten = nowPatten;

	ri.g = 0;
	ri.b = 0;

	srand((unsigned int)time(NULL));
}

void Boss::Update(float deltaTime)
{
	switch (nowPatten)
	{
	case 1:
		SwirlPatten(deltaTime, 50); break;
	case 2:
		SwirlPatten(deltaTime, -50); break;
	case 3:
		FlowerPatten(deltaTime); break;
	case 4:
		CirclePatten(deltaTime); break;
	}

	if (pattenTime > 3.0f)
	{
		nowPatten = 0;

		restTimer += deltaTime;

		if (restTimer > restTime)
		{
			pattenTime = 0.0f;
			restTimer = 0.0f;

			while (true)
			{
				bulletSpd = 100;

				nowPatten = rand() % 4 + 1;

				if (nowPatten != pastPatten)
					break;

			}
			pastPatten = nowPatten;
		}
		
		if (!fillBullet)
		{
			if (bulletTimer > bulletTime )
			{
				bulletTimer = 0.0f;

				EnemyBullet* bullet;
				for (int i = 0; i < 6; ++i)
				{
					SceneManager::GetInstance().curScene->objManager.AddObject(bullet = new EnemyBullet(pos, i * (360 / 6) + (rotate * 1), 100.0f, 2.0f));
					bulletVec.push_back(bullet);
				}
			}

			bulletTimer += deltaTime;
		}
	}

	pattenTime += deltaTime;

	if (bulletVec.size() > 75)
	{
		for (auto bullet : bulletVec)
		{
			auto distance = static_cast<GameScene*>(SceneManager::GetInstance().curScene)->player->pos - bullet->pos;
			D3DXVec2Normalize(&distance, &distance);
			bulletDis.push_back(distance);
		}

		fillBullet = true;
	}

	if (bulletVec.size() < 1)
	{
		bulletDis.clear();
		bulletVec.clear();
		fillBullet = false;
	}

	if (fillBullet)
	{
		int count = 0;
		for (auto bullet : bulletVec)
		{
			bullet->pos += bulletDis[count++] * deltaTime * 300;
		}

		for (auto bullet = bulletVec.begin(); bullet != bulletVec.end();)
		{
			if ((*bullet)->destroy)
				bullet = bulletVec.erase(bullet);
			else
				++bullet;
		}
	}

	Hit(deltaTime);
	Object::Update(deltaTime);
}

void Boss::OnCollision2D(Collider2D& _colider2D)
{
	if (_colider2D.tag == L"PlayerBullet")
	{
		hp--;

		if (!isHit)
			isHit = true;
	}
}

void Boss::Render()
{
	ri.pos = pos;
	spr2D.Render(ri);
	Object::Render();
}

void Boss::SwirlPatten(float deltaTime, float rotateRate)
{
	if (bulletTimer > bulletTime)
	{
		bulletTimer = 0.0f;
		Attack(6, 100, 0.2f, 1);
	}

	ri.rotate += rotateRate * 6 * deltaTime;
	rotate += rotateRate * deltaTime;
	bulletTimer += deltaTime;

}

void Boss::FlowerPatten(float deltaTime)
{
	if (bulletTimer > bulletTime)
	{
		bulletTimer = 0.0f;
		Attack(6, 100, 0.4f, 1);
		Attack(6, 100, -0.4f, -1, D3DCOLOR_ARGB(255, 0, 0, 255));
	}

	ri.rotate -= 600 * deltaTime;
	rotate += 50 * deltaTime;
	bulletTimer += deltaTime;
}

void Boss::CirclePatten(float deltaTime)
{
	if (bulletTimer > bulletTime)
	{
		bulletTimer = 0.0f;
		for (int i = 0; i < 36; ++i)
			SceneManager::GetInstance().curScene->objManager.AddObject(new EnemyBullet(pos, float(i * 10), bulletSpd, 0.1f));

		bulletSpd += 10;
	}

	bulletTimer += deltaTime;
}

void Boss::Attack(int BulletCreate, float speed, float angleRate, int rotateDir, D3DXCOLOR color)
{
	for (int i = 0; i < BulletCreate; ++i)
		SceneManager::GetInstance().curScene->objManager.AddObject(new EnemyBullet(pos, i * (360 / BulletCreate) + (rotate * rotateDir), speed, angleRate, color));
}

void Boss::Hit(float deltaTime)
{
	if (isHit)
	{
		hitTime += deltaTime;

		if (hitTime < 0.1f)
		{
			ri.g += 1999 * deltaTime;
			ri.b += 1999 * deltaTime;
		}
		else
		{
			hitTime = 0.0f;
			ri.g = 0;
			ri.b = 0;
			isHit = false;
		}
	}

	if (hp <= 0)
	{
		for (auto bullet = bulletVec.begin(); bullet != bulletVec.end();)
		{
			if ((*bullet) != NULL)
			{
				(*bullet)->destroy = true;
				bullet = bulletVec.erase(bullet);
			}
			else
				++bullet;
		}

		destroy = true;
		static_cast<GameScene*>(SceneManager::GetInstance().curScene)->enemySpawner->spawnBoss = false;
	}
}
