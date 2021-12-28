#include "Core.h"

IBullet::IBullet(D3DXVECTOR2 pos, float angle, float speed, std::wstring tag, float angleRate)
{
	spr2D.LoadAll(L"Assets/Sprites/Pixel.png");

	this->tag = tag;

	Collider2D::Circle circle;
	circle.radius = 3.0f;
	bodies.push_back(Collider2D(this, tag, nullptr, nullptr, &circle));

	this->pos = pos;
	this->angleRate = angleRate;
	ri.rotate = -angle;
	radian = D3DXToRadian(angle);

	this->speed = speed;

	ri.scale = { 0.7f, 0.2f };

	layer = -2;	
	colliderLayer = COLLIDERLAYER::CL_BULLET;
}

void IBullet::Update(float deltaTime)
{
	radian += angleRate * deltaTime;

	pos += D3DXVECTOR2(cosf(radian), sinf(radian)) * speed * deltaTime;

	float screenWidth = Direct3D::GetInstance().resolutionWidth;
	float screenHeight = Direct3D::GetInstance().resolutionHeight;

	if (pos.x >= screenWidth / 2 || pos.x <= -screenWidth / 2 || pos.y >= screenHeight / 2 || pos.y <= -screenHeight / 2)
		destroy = true;

	Object::Update(deltaTime);
}

void IBullet::Render()
{
	ri.pos = pos;
	spr2D.Render(ri);
}
