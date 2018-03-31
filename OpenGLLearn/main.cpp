#include <Windows.h>
#include "vld.h"
#include "CTexture.h"
#include "CGPUProgram.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"
#include "CSphere.h"
#include "CCamera.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "winmm.lib")


static unsigned int Pos_Left       = 100;
static unsigned int Pos_Top        = 100;
static unsigned int ViewPortWidth  = 800;
static unsigned int ViewPortHeight = 600;
static GLdouble fovy               = 45.0f;                        //eye opened angle
static GLdouble aspect             = 1.2f;                         //ViewPortWidth/ViewPortHeight;
static GLdouble zNear              = 0.1f, zFar = 100.0f;          //the neareast and farest distance which eye can see;


CTexture    texture[2];
CGPUProgram program;
CSphere     earth;
CCamera     camera;

POINT      originalPos;
bool       bRotateView = false;

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

	texture[0].init("res/images/earth/earthsatellite.bmp");
	texture[1].init("res/images/earth/earthcloudmap.bmp");

	earth.Init("");

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

	static float degree = 0.0f;
	degree += 0.1f;
	if (degree >= 360)
	{
		degree =degree - 360.0f;
	}
	glm::mat4 TranslateMat= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 RotateMat   = glm::rotate(glm::mat4(1.0), degree, glm::vec3(0.3, 1.0, 0.02));
	glm::mat4 ScaleMat    = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	glm::mat4 ModelMatrix = TranslateMat * RotateMat * ScaleMat; 
	//glm::mat4 ViewMatrix = glm::mat4(1.0f);
	glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(camera.mPosition.x, camera.mPosition.y, camera.mPosition.z), glm::vec3(camera.mViewCenter.x, camera.mViewCenter.y, camera.mViewCenter.z), glm::vec3(camera.mUp.x, camera.mUp.y, camera.mUp.z));
	glm::mat4 ProjMatrix = glm::perspective<float>((GLfloat)fovy, (GLfloat)aspect, (GLfloat)zNear, (GLfloat)zFar);


	// clear color buffer and depth buffer
	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(program.mProgram);
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

	earth.Bind(program.GetLocation("position"), program.GetLocation("normal"), program.GetLocation("texcoord"));
	earth.Draw();
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

	return 0;
}