#include "Core.h"

void Sprite::LoadAll(std::wstring _filePath)
{
	filePath = _filePath;
	if (std::filesystem::is_directory(filePath))
	{
		for (auto& file : std::filesystem::recursive_directory_iterator(filePath))
		{
			if (auto texture = TextureManager::GetInstance().GetTexture(file.path()))
				textures.push_back(texture);
		}
	}
	else
	{
		if (auto texture = TextureManager::GetInstance().GetTexture(filePath))
			textures.push_back(texture);
	}
	szScene = (int)textures.size();
}

bool Sprite::Update(float deltaTime)
{
	aniTime += deltaTime;
	if (aniTime >= aniMaxTime)
	{
		if (++scene >= szScene)
		{
			scene = szScene - 1;
			if (aniLoop)
				scene = 0;
			return true;
		}
		aniTime -= aniMaxTime;
	}
	return false;
}

void Sprite::Render(const RenderInfo & _ri)
{
	auto& d3dInst = Direct3D::GetInstance();

	// Texture set
	const Texture* texture = NULL;
	if (scene < szScene && scene >= 0)
		texture = textures[scene];
	else
		texture = TextureManager::GetInstance().GetTexture(L"Assets/NO_FOUND.png");

	// Vertex buffer set
	void* data;
	if (FAILED(d3dInst.pVB->Lock(0, 0, &data, 0)))
	{
		assert(0);
		return;
	}
	CUSTOMVERTEX v[4];
	v[0].pos = D3DXVECTOR3(0.0f, (float)texture->info.Height, 0.0f);
	v[0].diffuse = D3DCOLOR_ARGB(int(_ri.a), int(_ri.r), int(_ri.g), int(_ri.b));
	v[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	v[1].pos = D3DXVECTOR3((float)texture->info.Width* _ri.widthRatio, (float)texture->info.Height, 0.0f);
	v[1].diffuse = D3DCOLOR_ARGB(int(_ri.a), int(_ri.r), int(_ri.g), int(_ri.b));
	v[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	v[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	v[2].diffuse = D3DCOLOR_ARGB(int(_ri.a), int(_ri.r), int(_ri.g), int(_ri.b));
	v[2].uv = D3DXVECTOR2(0.0f, 1.0f);
	v[3].pos = D3DXVECTOR3((float)texture->info.Width * _ri.widthRatio, 0.0f, 0.0f);
	v[3].diffuse = D3DCOLOR_ARGB(int(_ri.a), int(_ri.r), int(_ri.g), int(_ri.b));
	v[3].uv = D3DXVECTOR2(1.0f, 1.0f);
	memcpy(data, (void*)v, sizeof(v));
	d3dInst.pVB->Unlock();

	// Sprite matrix set
	D3DXMATRIX mat;
	D3DXVECTOR2 scaleCen = _ri.scaleCen + _ri.center;
	scaleCen = D3DXVECTOR2(scaleCen.x * texture->info.Width, scaleCen.y * texture->info.Height);
	D3DXVECTOR2 rotateCen = _ri.rotateCen + _ri.center;
	rotateCen = D3DXVECTOR2(rotateCen.x * texture->info.Width, rotateCen.y * texture->info.Height);
	D3DXVECTOR2 position = _ri.pos - D3DXVECTOR2(_ri.center.x * texture->info.Width, _ri.center.y * texture->info.Height);
	D3DXMatrixTransformation2D(&mat, &scaleCen, 0.0f, &_ri.scale, &rotateCen, D3DXToRadian(-_ri.rotate), &position);

	// Draw
	d3dInst.pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	d3dInst.pD3DDevice->SetStreamSource(0, d3dInst.pVB, 0, sizeof(CUSTOMVERTEX));
	d3dInst.pD3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	d3dInst.pD3DDevice->SetTexture(0, texture->src);
	d3dInst.pD3DDevice->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, 0, 2);
}

void Sprite::Reset()
{
	scene = 0;
	aniTime = 0.0f;
}
