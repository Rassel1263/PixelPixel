#include "Core.h"

const Texture * TextureManager::GetTexture(std::wstring filePathWithName)
{
	auto tf = textureMaps.find(filePathWithName);
	if (tf != textureMaps.end())
		return tf->second;

	LPDIRECT3DTEXTURE9 src;
	D3DXIMAGE_INFO info;
	auto& d3dinst = Direct3D::GetInstance();

	if (FAILED(D3DXCreateTextureFromFileEx(d3dinst.pD3DDevice,
		filePathWithName.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&info,
		NULL,
		&src)))
	{
		wprintf(L"%s image can't found.\n", filePathWithName.c_str());
		return nullptr;
	}

	auto ti = textureMaps.insert(make_pair(filePathWithName, new Texture()));
	ti.first->second->info = info;
	ti.first->second->src = src;
	return ti.first->second;
}

void TextureManager::Terminate()
{
	for (auto textureMap : textureMaps)
	{
		textureMap.second->src->Release();
		delete textureMap.second;
	}
}
