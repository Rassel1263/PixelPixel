#include "Core.h"

Background::Background()
{
	progressBar.LoadAll(L"Assets/Sprites/Bar.png");
	progressInfo.scale.x = 0.0f;
	progressInfo.r = 50;
	layer = 1;
	progressInfo.pos.y = -175;

	expBar.LoadAll(L"Assets/Sprites/Bar.png");
	expInfo.scale.x = 0.0f;
	expInfo.r = expInfo.b = 0;
	expInfo.pos.y = -165;
	layer = 1;
}

void Background::Update(float deltaTime)
{
	float exp = static_cast<GameScene*>(SceneManager::GetInstance().curScene)->player->exp;
	float progress = static_cast<GameScene*>(SceneManager::GetInstance().curScene)->progress * 0.01f;

	D3DXVECTOR2 expLerp = D3DXVECTOR2(exp, 1.0f);
	D3DXVECTOR2 progressLerp = D3DXVECTOR2(progress, 1.0f);

	D3DXVec2Lerp(&expInfo.scale, &expInfo.scale, &expLerp, 0.01f);
	D3DXVec2Lerp(&progressInfo.scale, &progressInfo.scale, &progressLerp, 0.01f);

	Object::Update(deltaTime);
}

void Background::Render()
{
	progressBar.Render(progressInfo);
	expBar.Render(expInfo);
}
