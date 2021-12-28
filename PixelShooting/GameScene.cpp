#include "Core.h"

GameScene::GameScene()
{
	objManager.AddObject(player = new Player());
	enemySpawner = new EnemySpawner();
	objManager.AddObject(new Background());
}

void GameScene::Update(float deltaTime)
{
	if(!enemySpawner->spawnBoss)
		progress += deltaTime;

	enemySpawner->Update(deltaTime);
	Scene::Update(deltaTime);
}

void GameScene::FixedUpdate(float _fixedDeltaTime)
{
	Scene::FixedUpdate(_fixedDeltaTime);
}

void GameScene::UiRender()
{
	Scene::UiRender();
}
