#pragma once
class Background : public Object
{
public:
	Sprite progressBar, expBar;
	Sprite::RenderInfo progressInfo, expInfo;

	Background();

	virtual void Update(float deltaTime);
	virtual void Render();
};

