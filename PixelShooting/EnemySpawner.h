#pragma once

class EnemySpawner
{
public:
	Boss* boss = nullptr;
	Enemy* enemy = nullptr;

	std::vector<Enemy*> enemyList;

	bool spawnBoss = false;
	float spawnTime = 0.0f;
	int difficulty = 1;

public:
	EnemySpawner() {}

	virtual void Update(float deltaTime);
};

