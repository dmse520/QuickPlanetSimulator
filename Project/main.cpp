// Defines the entry point for the application.
//

#include "stdafx.h"

#include "MainWindow.h"

#define MAX_LOADSTRING 100

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	MainWindow win;

	if (!win.Create(TEXT("Planet Simulator"), WS_OVERLAPPEDWINDOW))
		return 0;

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = { };

    // Main message loop:
    while (msg.message != WM_QUIT)
    {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		win.WaitTimer();
    }

    return 0;
}