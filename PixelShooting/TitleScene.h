#pragma once
class TitleScene : public Scene
{
public:
	TitleScene();

	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float deltaTime) override;
};

