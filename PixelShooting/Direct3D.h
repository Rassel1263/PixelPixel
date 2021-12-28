#pragma once

struct CUSTOMVERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR diffuse;
	D3DXVECTOR2 uv;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class Direct3D
{
private:

	Direct3D() {}
	Direct3D(const Direct3D&) = delete;
	void operator = (const Direct3D&) = delete;

public:

	static Direct3D& GetInstance()
	{
		static Direct3D instance;
		return instance;
	}

private:

	bool firstUpdate = false;
	DWORD prevTime = 0;
	DWORD curTime = 0;
	float fpsTime = 0.0f;
	float fixedTime = 0.0f;
	float renderTime = 0.0f, renderDeltaTime = 1.0f / 60.0f;
	int fps = 0, curFps = 0;

public:
	bool cameraHandling = false;
	D3DXVECTOR2 cameraPos = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 cameraScale = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 cameraQuaken = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 destCameraPos = cameraPos;
	D3DXVECTOR2 destCameraScale = cameraScale;
	D3DXVECTOR2 destCameraQuaken = D3DXVECTOR2(0.0f, 0.0f);

public:

	HWND hWnd = NULL;
	LPDIRECT3D9 pD3D = NULL;
	LPDIRECT3DDEVICE9 pD3DDevice = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	LPD3DXFONT pFont = NULL;
	LPD3DXLINE pLine = NULL;

	int screenWidth = 0;
	int screenHeight = 0;
	float resolutionWidth = 640.0f;
	float resolutionHeight = 360.0f;
	float deltaTime = 0.0f;
	float fixedDeltaTime = 0.02f;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;

	void DrawLine(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, const D3DXMATRIX& mat);

	HRESULT Initialize(HWND _hWnd, int _screenWidth, int _screenHeight);
	void Terminate();
	void GameLoop();
};