#pragma once

class GameScene : public Scene
{
public:
	float progress = 0.0f;
	Player* player;
	Boss* boss;
	EnemySpawner* enemySpawner;

	GameScene();

	virtual void Update(float deltaTime) override;
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void UiRender() override;
};