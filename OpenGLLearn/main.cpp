#include <Windows.h>
#include "CTexture.h"
#include "CGPUProgram.h"
#include "CObjModel.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"

//#include "CGlmLearn.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")


static unsigned int Pos_Left       = 100;
static unsigned int Pos_Top        = 100;
static unsigned int ViewPortWidth  = 800;
static unsigned int ViewPortHeight = 600;
static GLdouble fovy               = 45.0f;                        //eye opened angle
static GLdouble aspect             = 1.2f;                         //ViewPortWidth/ViewPortHeight;
static GLdouble zNear              = 0.1f, zFar = 100.0f;         //the neareast and farest distance which eye can see;


CTexture    texture[2];
CGPUProgram program;
CObjModel   objmodel;
//CGlmLearn   glmlearn;

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


void init()
{
	glewInit();

	// init OpenGL
	/*
	glMatrixMode(GL_PROJECTION);
	GLdouble fovy   = 50.0f;                        //eye opened angle
	GLdouble aspect = ViewPortWidth/ViewPortHeight; //width / height
	GLdouble zNear  = 0.1f, zFar = 1000.0f;         //the neareast and farest distance which eye can see;
	gluPerspective(fovy, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/

	texture[0].init("res/images/earth/earthsatellite.bmp");
	texture[1].init("res/images/earth/earthcloudmap.bmp");

	objmodel.LoadModel("res/modules/Sphere.obj");

	program.AttatchShader(GL_VERTEX_SHADER,    "res/shaders/objmodel.vs");
	program.AttatchShader(GL_FRAGMENT_SHADER,  "res/shaders/objmodel.fs");
	program.Link();
	program.DetectAttribute("position");
	program.DetectAttribute("normal");
	program.DetectAttribute("texcoord");
	program.DetectUniform("M");
	program.DetectUniform("V");
	program.DetectUniform("P");
	program.DetectUniform("U_SatelliteTexture");
	program.DetectUniform("U_WeatherTexture");

}

void drawSence()
{
	glLoadIdentity();

	// clear color buffer and depth buffer
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glUseProgram(program.mProgram);

	glm::mat4 TranslateMat= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 RotateMat   = glm::rotate(glm::mat4(1.0), 0.0f, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 ScaleMat    = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	
	glm::mat4 ModelMatrix = TranslateMat * RotateMat * ScaleMat; 

	glm::mat4 ViewMatrix = glm::mat4(1.0f);

	glm::mat4 ProjMatrix = glm::perspective<float>(fovy, aspect, zNear, zFar);


	glUniformMatrix4fv(program.GetLocation("M"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(program.GetLocation("V"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(program.GetLocation("P"), 1, GL_FALSE, glm::value_ptr(ProjMatrix));

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0].mTextureId);
	glUniform1i(program.GetLocation("U_SatelliteTexture"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1].mTextureId);
	glUniform1i(program.GetLocation("U_WeatherTexture"),   1);

	objmodel.Bind(program.GetLocation("position"), program.GetLocation("normal"), program.GetLocation("texcoord"));
	objmodel.Draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	
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

	// create the window
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGLLearn", WS_OVERLAPPEDWINDOW, Pos_Left,Pos_Top, ViewPortWidth, ViewPortHeight, NULL,NULL,hInstance,NULL);

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

		// draw scene at the back
		drawSence();

		// present scene to window
		SwapBuffers(dc);
	}

	return 0;
}