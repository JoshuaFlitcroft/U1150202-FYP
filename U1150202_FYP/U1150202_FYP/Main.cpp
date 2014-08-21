//#include <Windows.h>
#include <memory>

#include "Engine.h"
// Checks for Memory Leaks.
#include "vld.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/**
	Win main taken from "Beginning DirectX 11 Game Programming" by Wendy Jones and Allen Sherrod.
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine,
					int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);
	
	WNDCLASSEX wndClass = {0};
	wndClass.cbSize = sizeof( WNDCLASSEX );
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "FYPClass";

	if (!RegisterClassEx(&wndClass))
		return - 1;

	RECT rc = {0, 0, 640, 480};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowA("FYPClass", "U1150202 - FYP", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, rc.right - rc.left, rc.bottom- rc.top, NULL, NULL, hInstance, NULL);

	if (!hwnd)
		return - 1;

	ShowWindow(hwnd, cmdShow);

	std::auto_ptr<DXEngineBase> demo(new Engine());

	// Demo Initialize.
	bool result = demo->Initialize(hInstance, hwnd);

	// Error reporting if there is an issue.
	if (result == false)
		return -1;

	MSG msg = {0};

	DWORD test = timeGetTime();

	float previousTime = (float)timeGetTime();
	float currentTime;
	// Don't want delta time to be greater than this.
	float maxStep = 1 / 60.0f;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			currentTime = (float)timeGetTime();

			// Update and Draw.
			// Calculate and pass in delta time - limiting it to make sure it doesn't exceed our limit.
			demo->Update(min(((currentTime - previousTime) / 1000.0f), maxStep));
			demo->Render();

			previousTime = currentTime;
		}
	}

	// Demo Shutdown.
	demo->Shutdown();

	return static_cast<int>(msg.wParam);
}

/**
	Taken from "Beginning DirectX 11 Game Programming" by Wendy Jones and Allen Sherrod.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}