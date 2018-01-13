#include <Windows.h>

// define a self message process function
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

INT WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	// create a  window class to define window info
	WNDCLASSEX wndclass;
	wndclass.cbSize        = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hbrBackground = NULL; //(HBRUSH)COLOR_HIGHLIGHT;
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);;
	wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm       = NULL; // LoadIcon(NULL, IDI_EXCLAMATION);;
	wndclass.hInstance     = hInstance;
	wndclass.lpfnWndProc   = MyWndProc;
	wndclass.lpszClassName = L"GLWindow";
	wndclass.lpszMenuName  = NULL;
	wndclass.style         = CS_VREDRAW | CS_HREDRAW;
	
	// register the window class
	ATOM  atom = RegisterClassEx(&wndclass);
	if (!atom)
	{
		return -1;
	}

	// create the window
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGLLearn", WS_OVERLAPPEDWINDOW, 100,100, 800, 600, NULL,NULL,hInstance,NULL);

	// show the window
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	// loop message
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg,NULL,NULL,NULL,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}