#include "Core.h"

Scene::~Scene()
{
}

void Scene::Update(float deltaTime)
{
	objManager.Update(deltaTime);
}

void Scene::FixedUpdate(float _fixedDeltaTime)
{
	objManager.FixedUpdate(_fixedDeltaTime);
}

void Scene::Render()
{
	objManager.Render();
}

void Scene::UiRender()
{
	objManager.UiRender();
}

SceneManager::~SceneManager()
{
	for (auto sceneMap : scenes)
		delete sceneMap.second;
}

Scene * SceneManager::GetScene(const std::wstring & _name)
{
	auto sf = scenes.find(_name);
	if (sf != scenes.end())
		return sf->second;
	return NULL;
}

void SceneManager::AddScene(const std::wstring & _name, Scene * _add)
{
	RemoveScene(_name);
	scenes[_name] = _add;
}

void SceneManager::RemoveScene(const std::wstring & _name)
{
	auto sf = scenes.find(_name);
	if (sf != scenes.end())
	{
		delete sf->second;
		scenes.erase(sf);
	}
}

void SceneManager::ChangeScene(const std::wstring & _name)
{
	nextScene = scenes[_name];
}

bool SceneManager::IsChangeScene()
{
	return nextScene != NULL;
}

void SceneManager::Update(float deltaTime)
{
	if (loading2D.szScene == 0)
	{
		loading2D.LoadAll(L"Assets/Loading");
	}

	if (nextScene)
	{
		loadingRenderInfo.a += deltaTime * 100.0f;
		if (loadingRenderInfo.a >= 1.0f)
		{
			curScene = nextScene;
			nextScene = NULL;
			loadingRenderInfo.a = 1.0f;
		}
	}
	else
	{
		loadingRenderInfo.a -= deltaTime * 2.0f;
		if (loadingRenderInfo.a <= 0.0f)
			loadingRenderInfo.a = 0.0f;
	}

	if (curScene)
	{
		curScene->Update(deltaTime);
	}
}

void SceneManager::FixedUpdate(float _fixedDeltaTime)
{
	if (curScene)
		curScene->FixedUpdate(_fixedDeltaTime);
}

void SceneManager::Render()
{
	if (curScene)
		curScene->Render();
}

void SceneManager::UiRender()
{
	if (curScene)
		curScene->UiRender();

	loading2D.Render(loadingRenderInfo);
}
