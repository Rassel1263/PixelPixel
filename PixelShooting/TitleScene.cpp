#include "Core.h"

TitleScene::TitleScene()
{            
	objManager.AddObject(new Button(L"Assets/Sprites/PixelPixel.png", D3DXVECTOR2(0.0f, 120.0f), Button::ButtonKind::None));
	objManager.AddObject(new Button(L"Assets/Sprites/Start.png", D3DXVECTOR2(0.0f, 0.0f), Button::ButtonKind::Start));
	objManager.AddObject(new Button(L"Assets/Sprites/Exit.png", D3DXVECTOR2(0.0f, -100.0f), Button::ButtonKind::Exit));
	objManager.AddObject(new Mouse());
}

void TitleScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void TitleScene::FixedUpdate(float deltaTime)
{
	Scene::FixedUpdate(deltaTime);
}

