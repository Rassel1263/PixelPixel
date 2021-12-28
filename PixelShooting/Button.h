#pragma once
class Button : public Object
{
public:
	enum class ButtonKind
	{
		None,
		Start,
		Exit,
		End,
	} kind;
public:
	float a = 1.3f;

	Sprite spr2D;
	Sprite::RenderInfo ri;

	Button(std::wstring name, D3DXVECTOR2 pos, ButtonKind kind);

	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float fixedDeltaTime) override;
	virtual void Render() override;
	virtual void OnCollision2D(Collider2D& _collider2D) override;
};

