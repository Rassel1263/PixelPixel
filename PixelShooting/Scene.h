#pragma once

class Scene
{
public:

	ObjectManager objManager;

	virtual ~Scene();
	virtual void Update(float deltaTime);
	virtual void FixedUpdate(float _fixedDeltaTime);
	virtual void Render();
	virtual void UiRender();
};

class SceneManager
{
private:

	SceneManager() {}
	SceneManager(const SceneManager&) = delete;
	void operator = (const SceneManager&) = delete;

public:

	static SceneManager& GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

private:

	std::map<std::wstring, Scene*> scenes;

	Sprite loading2D;
	Sprite::RenderInfo loadingRenderInfo;
	Sprite cursor2D;
	Sprite::RenderInfo cursorRenderInfo;

public:

	~SceneManager();

	Scene * curScene = NULL;
	Scene * nextScene = NULL;

	Scene * GetScene(const std::wstring& _name);
	void AddScene(const std::wstring& _name, Scene* _add);
	void RemoveScene(const std::wstring& _name);
	void ChangeScene(const std::wstring& _name);
	bool IsChangeScene();
	void Update(float deltaTime);
	void FixedUpdate(float _fixedDeltaTime);
	void Render();
	void UiRender();
};