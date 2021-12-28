#include "Core.h"

void Direct3D::DrawLine(const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, const D3DXMATRIX& mat)
{
	pLine->SetWidth(2.0f);
	pLine->Begin();
	auto lines = { D3DXVECTOR3(p1.x, p1.y, 0.0f), D3DXVECTOR3(p2.x, p2.y, 0.0f) };
	D3DXMATRIX matLine = mat * matView * matProj;
	pLine->DrawTransform(lines.begin(), lines.size(), &matLine, D3DCOLOR_ARGB(255, 255, 0, 0));
	pLine->End();
}

HRESULT Direct3D::Initialize(HWND _hWnd, int _screenWidth, int _screenHeight)
{
	// Init data & property
	hWnd = _hWnd;
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	
#ifdef _DEBUG
	// Show console.
	if (!AllocConsole())
		return E_FAIL;
	
	// Link console - wprintf...
	FILE *fDummy;
	freopen_s(&fDummy, "CON", "r", stdin);
	freopen_s(&fDummy, "CON", "w", stdout);
	freopen_s(&fDummy, "CON", "w", stderr);

	// Memory leak check.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Create the D3D object.
	if (NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = screenWidth;
	d3dpp.BackBufferHeight = screenHeight;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; 
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Create the D3DDevice
	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pD3DDevice)))
	{
		return E_FAIL;
	}

	// Create the vertex buffer.
	if (FAILED(pD3DDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &pVB, NULL)))
	{
		return E_FAIL;
	}
	
	// Create the font.
	if (FAILED(D3DXCreateFont(pD3DDevice, 0, 0, FW_DONTCARE, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"³ª´® °íµñ", &pFont)))
	{
		return E_FAIL;
	}

	// Create the line
	if (FAILED(D3DXCreateLine(pD3DDevice, &pLine)))
	{
		return E_FAIL;
	}

	// Turn off culling
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Turn off D3D lighting
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Turn on the zbuffer
	pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Alpha texture blend setting
	pD3DDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHABLENDENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3DDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	// Camera base setting.
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	SceneManager::GetInstance().AddScene(L"GameScene", new GameScene());
	SceneManager::GetInstance().AddScene(L"TitleScene", new TitleScene());
	SceneManager::GetInstance().ChangeScene(L"TitleScene");

	return S_OK;
}

void Direct3D::Terminate()
{
	SAFE_RELEASE(pD3D);
	SAFE_RELEASE(pD3DDevice);
	SAFE_RELEASE(pVB);
	SAFE_RELEASE(pFont);
	SAFE_RELEASE(pLine);
	
	TextureManager::GetInstance().Terminate();

#ifdef _DEBUG
	FreeConsole();
#endif
}

void Direct3D::GameLoop()
{
	// Time update 1
	curTime = timeGetTime();

	if (firstUpdate)
	{
		auto pastTime = curTime - prevTime;
		deltaTime = pastTime / 1000.0f;
	}
	fpsTime += deltaTime;
	fixedTime += deltaTime;
	curFps += 1;
	if (fpsTime >= 1.0f)
	{
		fps = curFps;
		curFps = 0;
		fpsTime = 0.0f;
	}
	
	Input::GetInstance().Update();

	if (fixedTime > 2.0f)
		fixedTime = 2.0f;
	while (fixedTime >= fixedDeltaTime)
	{
		fixedTime -= fixedDeltaTime;
		SceneManager::GetInstance().FixedUpdate(fixedDeltaTime);

		cameraPos += (destCameraPos - cameraPos) * 0.07f;
		cameraScale += (destCameraScale - cameraScale) * 0.07f;
		cameraQuaken += (destCameraQuaken - cameraQuaken) * 0.05f;
		// Fixed update logic
	}
	// Update logic
	SceneManager::GetInstance().Update(deltaTime);

	renderTime += deltaTime;
	if (renderTime > renderDeltaTime)
	{
		// Clear the backbuffer and the zbuffer
		pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		// Begin the scene
		if (SUCCEEDED(pD3DDevice->BeginScene()))
		{
			D3DXMatrixOrthoLH(&matProj, resolutionWidth, resolutionHeight, 0.01f, 1000.0f);
			D3DXMATRIX matCamScale;
			D3DXMatrixScaling(&matCamScale, cameraScale.x, cameraScale.y, 1.0f);
			D3DXMATRIX matCamPos;
			D3DXMatrixTranslation(&matCamPos, -cameraPos.x + (rand()%2 == 0 ? -1 : 1) * cameraQuaken.x, -cameraPos.y + (rand() % 2 == 0 ? -1 : 1) * cameraQuaken.y, 0.0f);
			matProj = matCamPos * matCamScale * matProj;
			pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
			SceneManager::GetInstance().Render();

			D3DXMatrixOrthoLH(&matProj, resolutionWidth, resolutionHeight, 0.01f, 1000.0f);
			pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
			SceneManager::GetInstance().UiRender();

	#ifdef _DEBUG
			// Draw fps, deltaTime
			wchar_t fpsBuffer[255];
			swprintf_s(fpsBuffer, L"FPS : %d, DeltaTime : %f", fps, deltaTime);
			auto rect = RECT{ 0,0,0,0 };
			pFont->DrawTextW(NULL, fpsBuffer, -1, &rect, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	#endif

			// End the scene
			pD3DDevice->EndScene();
		}

		// Present the backbuffer contents to the display
		pD3DDevice->Present(NULL, NULL, NULL, NULL);
		renderTime = 0.0f;
	}

	// Time update 2
	prevTime = curTime;
	firstUpdate = true;
}
