#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "CCamera.h"
#include "CEarth.h"
#include "CSkyBox.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

static unsigned int Pos_Left       = 10;
static unsigned int Pos_Top        = 10;
static unsigned int ViewPortWidth  = 1280;
static unsigned int ViewPortHeight = 700;
static CCamera   camera;
static CEarth    earth;
static CSkyBox   skybox;
POINT originalPos;
bool bRotateView = false;

void init()
{
	earth.init("res/modules/Sphere.obj", "res/images/earth.bmp");
	skybox.init("res/images/skybox/");

}

// define a self message process function
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_RBUTTONDOWN:
		originalPos.x = LOWORD(lParam);
		originalPos.y = HIWORD(lParam);
		ClientToScreen(hwnd, &originalPos);
		SetCapture(hwnd);
		ShowCursor(false);
		bRotateView = true;
		break;
	case WM_RBUTTONUP:
		bRotateView = false;
		SetCursorPos(originalPos.x, originalPos.y);
		ReleaseCapture();
		ShowCursor(true);
		break;
	case WM_MOUSEMOVE:
		if (bRotateView)
		{
			POINT currentPos;
			currentPos.x        = LOWORD(lParam);
			currentPos.y        = HIWORD(lParam);
			ClientToScreen(hwnd, &currentPos);
			int deltaX                = currentPos.x - originalPos.x;
			int deltaY                = currentPos.y - originalPos.y;
			float angleRotatedByRight = (float)deltaY / 1000.0f;
			float angleRotatedByUp    = (float)deltaX / 1000.0f;
			camera.Yaw(-angleRotatedByUp);
			camera.Pitch(-angleRotatedByRight);
			SetCursorPos(originalPos.x, originalPos.y);
		}
		break;
	case WM_KEYUP:
		switch(wParam)
		{
		case VK_LEFT:
		case 'A':
			camera.mbMoveLeft = false;
			break;
		case VK_RIGHT:
		case 'D':
			camera.mbMoveRight = false;
			break;
		case VK_UP:
		case 'W':
			camera.mbMoveForward = false;
			break;
		case VK_DOWN:
		case 'S':
			camera.mbMoveBackward = false;
			break;
		}
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_LEFT:
		case 'A':
			camera.mbMoveLeft = true;
			break;
		case VK_RIGHT:
		case 'D':
			camera.mbMoveRight = true;
			break;
		case VK_UP:
		case 'W':
			camera.mbMoveForward = true;
			break;
		case VK_DOWN:
		case 'S':
			camera.mbMoveBackward = true;
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

void drawSence(float timeElapse)
{
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	// draw scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set up camera
	camera.Update(timeElapse);

	skybox.Draw(camera.mPosition.x, camera.mPosition.y, camera.mPosition.z);

	earth.Draw();

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
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGLLearn", WS_OVERLAPPEDWINDOW, Pos_Left,Pos_Top, ViewPortWidth, ViewPortHeight, NULL,NULL,hInstance,NULL);

	// create OpenGL render content
	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0 , sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nVersion = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iPixelType   = PFD_TYPE_RGBA;
	pfd.iLayerType   = PFD_MAIN_PLANE;
	pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc,pixelFormat, &pfd);

	// setup OpenGL context
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	// init OpenGL
	glMatrixMode(GL_PROJECTION);
	GLdouble fovy   = 50.0f;                        //eye opened angle
	GLdouble aspect = ViewPortWidth/ViewPortHeight; //width / height
	GLdouble zNear  = 0.1f, zFar = 1000.0f;         //the neareast and farest distance which eye can see;
	gluPerspective(fovy, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);

	// show the window
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	//开启 面剔除功能，将看不到的背面剔除，不绘画;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	init();

	static float sTimeSinceStartUp = timeGetTime() / 1000.0f;

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

		float currentTime = timeGetTime() / 1000.0f;
		float timeElapse  = currentTime - sTimeSinceStartUp;
		sTimeSinceStartUp = currentTime;

		drawSence(timeElapse);

		// present scene to window
		SwapBuffers(dc);
	}

	return 0;
}