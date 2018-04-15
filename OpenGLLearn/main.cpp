#include <Windows.h>
#include "vld.h"
#include "CCamera.h"
#include "CSphere.h"
#include "CSkyBox.h"
#include "CBoundaryLayer.h"
#include "CSpriteImge.h"
#include "CTextureMgr.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "winmm.lib")

static  HWND hwnd                = NULL;
static  int Pos_Left             = 100;
static  int Pos_Top              = 100;
static  int ViewPortWidth        = 800;
static  int ViewPortHeight       = 600;

static Vector4F ViewPort(-ViewPortWidth/2, ViewPortHeight/2, ViewPortWidth/2, -ViewPortHeight/2);

CCamera                camera(ViewPort);
CSphere                earth(camera);
CSkyBox                skybox(camera);
CBoundaryLayer         boundarylayer(camera);
CSpriteImage           compass(camera);

RECT*      p_rect = NULL;
POINT      originalPos;
bool       bRotateView = false;

// define a self message process function
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_SIZE:
		ViewPortWidth  = LOWORD(lParam);
		ViewPortHeight = HIWORD(lParam);
		//std::cout<<"WM_SIZE...("<< width << "," <<  height << ")" << std::endl;
		ViewPort.left      = -ViewPortWidth/2;
		ViewPort.right     =  ViewPortWidth/2;
		ViewPort.top       =  ViewPortHeight/2;
		ViewPort.bottom    = -ViewPortHeight/2;
		glViewport(0, 0, ViewPortWidth, ViewPortHeight);
		camera.setViewport(ViewPort);
		compass.SetRect(-ViewPortWidth/2.0f + 128.0f/2, ViewPortHeight/2.0f - 128.f/2, 128.0f, 128.0f);
		break;
	case WM_SIZING:
		p_rect = (RECT*)lParam; 
		//std::cout<<"WM_SIZING...("<< p_rect->left << "," << p_rect->top << "," << p_rect->right << "," << p_rect->bottom << ")" << std::endl;
		//std::cout<<"WM_SIZING...("<< p_rect->right - p_rect->left << "," <<  p_rect->bottom - p_rect->top << ")" << std::endl;
		break;
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
			currentPos.x = LOWORD(lParam);
			currentPos.y = HIWORD(lParam);
			ClientToScreen(hwnd, &currentPos);
			int deltaX = currentPos.x - originalPos.x;
			int deltaY = currentPos.y - originalPos.y;
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


void init()
{
	// init OpenGL
	glewInit();

	skybox.Init("res/images/skybox");
	earth.Init("res/images/earth");
	boundarylayer.Init("res/others/countries.geo.json");
	compass.Init("res/images/south_north.jpg");
	compass.SetRect(-ViewPortWidth/2.0f + 128.0f/2, ViewPortHeight/2.0f - 128.f/2, 128.0f, 128.0f);
}

void drawSence()
{
	// clear color buffer and depth buffer
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	
	camera.SwitchTo3D();

	// draw sky box;
	skybox.Draw();

	// draw earth
	earth.Draw();
	
	// draw country boundary
	boundarylayer.Draw();
	
	// draw other scenes
	camera.SwitchTo2D();

	// draw ui compass
	compass.Draw();


	glFinish();
}


INT WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	//glmlearn.learn();

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

	RECT rect;
	rect.left          = 0;
	rect.right         = rect.left + ViewPortWidth;
	rect.top           = 0;
	rect.bottom        = rect.top  + ViewPortHeight;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);

	// create the window
	hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGLLearn", WS_OVERLAPPEDWINDOW, Pos_Left,Pos_Top, rect.right - rect.left, rect.bottom - rect.top, NULL,NULL,hInstance,NULL);

	// create OpenGL render content
	HDC dc = GetDC(hwnd);

	// define pixel format descriptor
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0 , sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion      = 1;
	pfd.nVersion      = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits    = 32;
	pfd.cDepthBits    = 24;
	pfd.cStencilBits  = 8;
	pfd.iPixelType    = PFD_TYPE_RGBA;
	pfd.iLayerType    = PFD_MAIN_PLANE;
	pfd.dwFlags       = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixelFormat = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc,pixelFormat, &pfd);

	// setup OpenGL context
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);

	// show the window
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

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
		float timeElapse = currentTime - sTimeSinceStartUp;
		sTimeSinceStartUp = currentTime;

		//set up camera
		camera.Update(timeElapse);

		// draw scene at the back
		drawSence();

		// present scene to window
		SwapBuffers(dc);
	}

	CTextureMgr::ClearCachedTextures();
	return 0;
}