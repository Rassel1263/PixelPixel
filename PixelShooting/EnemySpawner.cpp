#include "Core.h"

void EnemySpawner::Update(float deltaTime)
{
	spawnTime += deltaTime;
	float progress = static_cast<GameScene*>(SceneManager::GetInstance().curScene)->progress;

	if(!spawnBoss)
	if (spawnTime >= 1.0f)
	{
		SceneManager::GetInstance().curScene->objManager.AddObject(enemy = new Enemy(D3DXVECTOR2(float(rand() % 640 - 320), float(rand()% 360 - 180)), difficulty));
		enemyList.push_back(enemy);
		spawnTime = 0.0f;
	}

	if (progress >= 30.0f * difficulty)
	{
		sort(enemyList.begin(), enemyList.end());

		if (enemyList.size() != 0)
		{
			for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
			{
				if ((*it) != NULL)
					(*it)->OnDestroy();
			}
		}

		spawnBoss = true;
		difficulty++;
		SceneManager::GetInstance().curScene->objManager.AddObject(new Boss());
	}
}


