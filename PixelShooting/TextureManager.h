#pragma once

class Texture
{
public:
	LPDIRECT3DTEXTURE9 src;
	D3DXIMAGE_INFO info;
};

class TextureManager
{
private:

	TextureManager() {}
	TextureManager(const TextureManager&) = delete;
	void operator = (const TextureManager&) = delete;

public:

	static TextureManager& GetInstance()
	{
		static TextureManager instance;
		return instance;
	}

private:

	std::map<std::wstring, Texture*> textureMaps;

public:
	const Texture* GetTexture(std::wstring filePathWithName);
	void Terminate();
};