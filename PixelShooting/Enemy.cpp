#include "Core.h"

Enemy::Enemy(D3DXVECTOR2 pos, int enemyIndex)
{
	// ------------ 기본 설정 ------------ //
	spr2D.LoadAll(L"Assets/Sprites/Pixel.png");
	tag = L"Enemy";

	Collider2D::Circle circle;
	circle.radius = 10.0f;
	bodies.push_back(Collider2D(this, tag, nullptr, nullptr, &circle));
	colliderLayer = COLLIDERLAYER::CL_ENEMY;

	ri.scale = D3DXVECTOR2(0.0f, 0.0f);
	this->pos = pos;

	// ------------ enemyIndex ------------ //
	
	if(enemyIndex == 1)
		ri.g = ri.b = 0;

	if (enemyIndex == 2)
	{
		ri.g = 154;
		ri.b = 45;
	}

}

void Enemy::Update(float deltaTime)
{
	Hit(deltaTime);
	bulletTime += deltaTime;

	if (bulletTime >= 2.0f)
	{
		D3DXVECTOR2 playerPos = static_cast<GameScene*>(SceneManager::GetInstance().curScene)->player->pos;
		playerPos = playerPos - pos;
		D3DXVec2Normalize(&playerPos, &playerPos);
		float angle = -D3DXToDegree(atan2(playerPos.x, playerPos.y)) + 90;

		SceneManager::GetInstance().curScene->objManager.AddObject(new EnemyBullet(pos, angle, 700));
		bulletTime = 0.0f;
	}

	Object::Update(deltaTime);

}

void Enemy::Render()
{
	ri.pos = pos;
	spr2D.Render(ri);
}

void Enemy::OnCollision2D(Collider2D& _collider2D)
{
	if (_collider2D.tag == L"Player" || _collider2D.tag == L"PlayerBullet")
	{
		hp--;
		if (!isHit)
		{
			isHit = true;
		}

		for (int i = 0; i < 5; ++i)
		{
			float eftRotateX = (rand() % 19 - 9) * 0.1f;
			float eftRotateY = (rand() % 19 - 9) * 0.1f;
			SceneManager::GetInstance().curScene->objManager.AddObject(new HitEft(pos, D3DXVECTOR2(eftRotateX, eftRotateY), float(rand() % 200 + 100), Color{ 215, 255, 15, 15 }));
		}
	}
}

void Enemy::Hit(float deltaTime)
{
	if (isHit)
	{
		hitTime += deltaTime;

		if (hitTime < 0.1f)
		{
			D3DXVECTOR2 scaleLerp = D3DXVECTOR2(ri.scale.x + 0.01f, ri.scale.y + 0.01f);
			D3DXVec2Lerp(&ri.scale, &ri.scale, &scaleLerp, 0.1f);
			ri.a -= 700 * deltaTime;
		}
		else
		{
			hitTime = 0.0f;
			ri.a = 255;
			isHit = false;
		}
	}
	else
	{
		D3DXVECTOR2 scaleLerp = D3DXVECTOR2(1.0f, 1.0f);
		D3DXVec2Lerp(&ri.scale, &ri.scale, &scaleLerp, 0.01f);
	}

	if (hp <= 0)
	{
		OnDestroy();
		static_cast<GameScene*>(SceneManager::GetInstance().curScene)->player->exp += 0.1f;
	}
}

void Enemy::OnDestroy()
{
	for (int i = 0; i < 10; i++)
	{
		float eftRotateX = (rand() % 19 - 9) * 0.1f;
		float eftRotateY = (rand() % 19 - 9) * 0.1f;
		SceneManager::GetInstance().curScene->objManager.AddObject(new HitEft(pos, D3DXVECTOR2(eftRotateX, eftRotateY), float(rand() % 200 + 100), Color{ 215, 255, 15, 15 }));
	}

	destroy = true;
}
