#pragma once

class Sprite
{
public:

	std::vector<const Texture*> textures;

	int szScene = 0;
	int scene = 0;
	float aniTime = 0.0f;
	float aniMaxTime = 0.1f;
	bool aniLoop = true;
	std::wstring filePath;

public:

	class RenderInfo
	{
	public:
		D3DXVECTOR2 pos = D3DXVECTOR2(0.0f, 0.0f);
		D3DXVECTOR2 scaleCen = D3DXVECTOR2(0.0f, 0.0f);
		D3DXVECTOR2 scale = D3DXVECTOR2(1.0f, 1.0f);
		float rotate = 0.0f;
		D3DXVECTOR2 rotateCen = D3DXVECTOR2(0.0f, 0.0f);
		D3DXVECTOR2 center = D3DXVECTOR2(0.5f, 0.5f);
		float a = 255.0f, r = 255.0f, g = 255.0f, b = 255.0f;
		float widthRatio = 1.0f;
	};

	void LoadAll(std::wstring _filePath);
	bool Update(float deltaTime);
	void Render(const RenderInfo& _ri);
	void Reset();
};