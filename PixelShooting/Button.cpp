#include "Core.h"
#include "Object.h"

Button::Button(std::wstring name, D3DXVECTOR2 pos, ButtonKind kind)
{
	colliderLayer = COLLIDERLAYER::CL_ENEMY;

	spr2D.LoadAll(name);

	this->pos = pos;
	this->kind = kind;

	if (this->kind != ButtonKind::None)
	{
		tag = L"Button";

		Collider2D::AABB aabb;
		aabb.min = D3DXVECTOR2(-100, -25);
		aabb.max = D3DXVECTOR2(100, 25);
		bodies.push_back(Collider2D(this, tag, nullptr, &aabb, nullptr));
	}
}

void Button::Update(float deltaTime)
{
	auto mousePos = Input::GetInstance().GetWorldCursorPos();
	auto textureInfo = spr2D.textures[0]->info;
	if (mousePos.x > pos.x - textureInfo.Width / 2 && mousePos.x < pos.x + textureInfo.Width / 2 &&
		mousePos.y < pos.y + textureInfo.Height / 2 && mousePos.y > pos.y - textureInfo.Height / 2)
	{
		if (Input::GetInstance().GetKeyState(VK_LBUTTON) == InputState::Down && kind == ButtonKind::Start)
			SceneManager::GetInstance().ChangeScene(L"GameScene");

		if (Input::GetInstance().GetKeyState(VK_LBUTTON) == InputState::Down && kind == ButtonKind::Exit)
			PostQuitMessage(0);

	}

	Object::Update(deltaTime);
	 

}

void Button::FixedUpdate(float fixedDeltaTime)
{

	if (kind == ButtonKind::None)
	{
		if (ri.scale.x >= 1.25f || ri.scale.y >= 1.25f)
			a = 0.8f;

		if (ri.scale.x <= 0.85f || ri.scale.y <= 0.85f)
			a = 1.3f;

		D3DXVECTOR2 scaleLerp = D3DXVECTOR2(a, a);
		D3DXVec2Lerp(&ri.scale, &ri.scale, &scaleLerp, 0.05f);
	}
	else
	{
		D3DXVECTOR2 scaleLerp = D3DXVECTOR2(1.0f, 1.0f);
		D3DXVec2Lerp(&ri.scale, &ri.scale, &scaleLerp, 0.1f);
	}

	Object::FixedUpdate(fixedDeltaTime);

}

void Button::Render()
{
	ri.pos = pos;
	spr2D.Render(ri);
}

void Button::OnCollision2D(Collider2D&)
{
	D3DXVECTOR2 scaleLerp = D3DXVECTOR2(1.5f, 1.5f);
	D3DXVec2Lerp(&ri.scale, &ri.scale, &scaleLerp, 0.1f);
}
