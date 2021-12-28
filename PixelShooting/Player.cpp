#include "Core.h"

Player::Player() : Object()
{
	spr2D.LoadAll(TEXT("Assets/Sprites/Pixel.png"));
	tag = L"Player";

	Collider2D::Circle circle;
	circle.radius = 3.0f;
	bodies.push_back(Collider2D(this, tag, nullptr, nullptr, &circle));


	ri.scale = D3DXVECTOR2(0.5f, 0.5f);
	ri.r = ri.b = 0;

	// ÀÌ°Å ²û
	colliderLayer = COLLIDERLAYER::CL_PLAYER;
	// activeCollider2D = false;
}

void Player::Update(float deltaTime)
{
	if (!isDash)
		ri.scale = Move(deltaTime) ? D3DXVECTOR2(0.6f, 0.4f) : D3DXVECTOR2(0.5f, 0.5f);

	Dash(deltaTime);
	Hit(deltaTime);

	if (Input::GetInstance().GetKeyState(VK_LBUTTON) == InputState::Down)
		Shoot();

	if (Input::GetInstance().GetKeyState(VK_F1) == InputState::Down)
		LevelUp();

	if (exp >= 1.0f)
		LevelUp();

	if (hp <= 0)
		destroy = true;

	spr2D.Update(deltaTime);
	Object::Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;
	spr2D.Render(Sprite::RenderInfo{ ri });
	Object::Render();
}

void Player::OnCollision2D(Collider2D& _collider2D)
{
	if (_collider2D.tag == L"Enemy" || _collider2D.tag == L"EnemyBullet")
	{
		if (!isHit && !isDash)
		{
			hp--;
			isHit = true;

			ri.a = 100.0f;
			ri.g = 0.0f;
			ri.b = 255.0f;

			for (int i = 0; i < 10; ++i)
			{
				float eftRotateX = (rand() % 19 - 9) * 0.1f;
				float eftRotateY = (rand() % 19 - 9) * 0.1f;
				SceneManager::GetInstance().curScene->objManager.AddObject(new HitEft(pos, D3DXVECTOR2(eftRotateX, eftRotateY), float(rand() % 200 + 100), Color{ 255, 0, 255, 15 }));
				Direct3D::GetInstance().cameraQuaken += D3DXVECTOR2(2.0f, 2.0f);
			}
		}
	}
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 dir = { 0.0f, 0.0f };

	float borderWidth = Direct3D::GetInstance().resolutionWidth / 2;
	float borderHeight = Direct3D::GetInstance().resolutionHeight / 2;

	if (Input::GetInstance().GetKeyState('A') == InputState::Press && pos.x > -borderWidth)
		dir.x = -1;

	if (Input::GetInstance().GetKeyState('D') == InputState::Press && pos.x < borderWidth)
		dir.x = 1;

	if (Input::GetInstance().GetKeyState('W') == InputState::Press && pos.y < borderHeight)
		dir.y = 1;

	if (Input::GetInstance().GetKeyState('S') == InputState::Press && pos.y > -borderHeight)
		dir.y = -1;

	if (dir.x * dir.y == 1)
		ri.rotate = 135;
	else if (dir.x * dir.y == -1)
		ri.rotate = 45;
	else if (dir.y != 0)
		ri.rotate = 90;
	else
		ri.rotate = 0;

	if (dir.x != 0 || dir.y != 0)
	{
		if (eftTime > 0.02f)
		{
			eftTime = 0.0f;
			SceneManager::GetInstance().curScene->objManager.AddObject(new MoveEft(pos + D3DXVECTOR2(float(rand() % 4 - 2), float(rand() % 4 - 2)),
				D3DXVECTOR2(0.3f, 0.3f), Color{ 255, 160, 255, 160 }));
		}

		eftTime += deltaTime;
		pos += dir * 200 * deltaTime;
		return true;
	}

	return false;
}

void Player::Dash(float deltaTime)
{
	D3DXVECTOR2 dir = Input::GetInstance().GetWorldCursorPos() - ri.pos;
	D3DXVec2Normalize(&dir, &dir);
	float rotate = D3DXToDegree(atan2(dir.x, dir.y));

	if (Input::GetInstance().GetKeyState(VK_RBUTTON) == InputState::Down && dashCoolTime > 0.1f)
	{
		int bulletCreate = rand() % 30 + 20;
		for (int i = 0; i < bulletCreate; i++)
		{
			float bulletRotateX = (rand() % 10 - 5) * 0.1f;
			float bulletRotateY = (rand() % 10 - 5) * 0.1f;
			SceneManager::GetInstance().curScene->objManager.AddObject(new BulletEft(pos, -(dir + D3DXVECTOR2(bulletRotateX, bulletRotateY)), float(rand() % 200 + 100)));
			SceneManager::GetInstance().curScene->objManager.AddObject(new BoomEft(pos));
		}
		// 135 315   
		isDash = true;
		tempDir = dir;
	}

	dashCoolTime += deltaTime;

	if (isDash)
	{
		dashCoolTime = 0.0f;
		dashTime += deltaTime;
		if (dashTime < 0.1f)
		{
			pos += tempDir * 1000 * deltaTime;
			ri.scale = D3DXVECTOR2(0.7f, 0.3f);
			ri.rotate = rotate + 90;
		}
		else
		{
			dashTime = 0;
			isDash = false;
		}
	}
}

void Player::Shoot()
{
	D3DXVECTOR2 dir = Input::GetInstance().GetWorldCursorPos() - ri.pos;
	D3DXVec2Normalize(&dir, &dir);
	float angle = -D3DXToDegree(atan2(dir.x, dir.y)) + 90;

	if(bulletCount == 1)
	{ 
		SceneManager::GetInstance().curScene->objManager.AddObject(new Bullet(pos, angle));
	}

	if(bulletCount > 1)
	{
		for (int i = 0; i < bulletCount; i++)
		{
			SceneManager::GetInstance().curScene->objManager.AddObject(new Bullet(pos, angle + angleRange * ((float)i / (bulletCount - 1) - 0.5f)));
		}
	}

	int bulletCreate = rand() % 5 + 3;

	for (int i = 0; i < bulletCreate; i++)
	{
		float bulletRotateX = (rand() % 10 - 5) * 0.1f;
		float bulletRotateY = (rand() % 10 - 5) * 0.1f;
		SceneManager::GetInstance().curScene->objManager.AddObject(new BulletEft(pos, dir + D3DXVECTOR2(bulletRotateX, bulletRotateY), float(rand() % 200 + 100)));
	}
	Direct3D::GetInstance().cameraQuaken += D3DXVECTOR2(0.2f, 0.2f);
	wprintf(L"angle : %0f\n", angle);


}

void Player::Hit(float deltaTime)
{
	if (isHit)
	{
		if (ri.a <= 255)
		{
			ri.a += 100 * deltaTime;
			ri.g += 100 * deltaTime;
			ri.b -= 100 * deltaTime;

			D3DXVECTOR2 scaleLerp = D3DXVECTOR2(ri.scale.x + 0.01f, ri.scale.y + 0.01f);
			D3DXVec2Lerp(&ri.scale, &ri.scale, &scaleLerp, 0.1f);
		}
		else
		{
			ri.a = 255;
			ri.g = 255;
			ri.b = 0;
			isHit = false;
		}
	}
}

void Player::LevelUp()
{
	exp = 0.0f;
	bulletCount++;
	//angleRange -= 0.5f;
}
