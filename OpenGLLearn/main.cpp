#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "CTexture.h"
#include "CObjModel.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

static unsigned int Pos_Left       = 10;
static unsigned int Pos_Top        = 10;
static unsigned int ViewPortWidth  = 1280;
static unsigned int ViewPortHeight = 700;
static CTexture  earth_texture;
static CObjModel earth_obj;

void init()
{
	earth_texture.init("res/images/earth.bmp");
	earth_obj.Init("res/modules/Sphere.obj");
}

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

void drawSence()
{
	glLoadIdentity();

	// draw scene
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earth_texture.mTextureId);
	earth_obj.Draw();
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

		drawSence();

		// present scene to window
		SwapBuffers(dc);
	}

	return 0;
}