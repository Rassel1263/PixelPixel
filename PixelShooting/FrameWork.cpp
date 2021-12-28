#include "Core.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_CHAR:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;
    case WM_DESTROY:
		PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT ){
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 05: FrameWork",
                              WS_POPUP, 200, 200, 1280, 720,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
	if (SUCCEEDED(Direct3D::GetInstance().Initialize(hWnd, 1280, 720)))
    {
        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        // Enter the message loop
        MSG msg;
        ZeroMemory( &msg, sizeof( msg ) );
        while( msg.message != WM_QUIT )
        {
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				Direct3D::GetInstance().GameLoop();
        }
    }

	Direct3D::GetInstance().Terminate();
	UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}

