#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

static unsigned int Pos_Left       = 10;
static unsigned int Pos_Top        = 10;
static unsigned int ViewPortWidth  = 1280;
static unsigned int ViewPortHeight = 700;

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
	// draw scene
	glClear(GL_COLOR_BUFFER_BIT);

	// draw point
	{
		glPointSize(20.0f);
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_BLEND);
		glBegin(GL_POINTS);
			glColor4ub(255, 0, 0, 255);
			glVertex3f(-1.0f, 4.0f, -10.0f);

			glColor4ub(0, 255, 0, 255);
			glVertex3f(0.0f, 4.0f, -10.0f);

			glColor4ub(0, 0 ,255,255);
			glVertex3f(1.0f, 4.0f, -10.0f);
		glEnd();

		glPointSize(15.0f);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_BLEND);
		glBegin(GL_POINTS);
			glVertex3f(-2.0f, 4.0f, -10.0f);
			glVertex3f(2.0f,  4.0f, -10.0f);
		glEnd();
		
	}

	// draw line
	{
		glLineWidth(3.0f);
		glColor4ub(255, 0, 0, 255);
		/*
		GL_LINES: the line count = (int)(point count / 2)
		*/
		glBegin(GL_LINES);
			// p0
			glVertex3f(-6.0f, 2.5f, -10.0f);
			// p1
			glVertex3f(-3.0f, 2.5f, -10.0f);
			// p2
			glVertex3f(-6.0f, 1.5f, -10.0f);
			// p3
			glVertex3f(-3.0f, 1.5f, -10.0f);
			// p4
			glVertex3f(-3.0f, 1.0f, -10.0f);
		glEnd();


		glColor4ub(0, 255, 0, 255);
		/*
		GL_LINE_STRIP : line count == pt count -1; 
		p0->p1; p1->p2; p2-p3
		*/
		glBegin(GL_LINE_STRIP);
			// p0
			glVertex3f(-2.5f, 2.5f, -10.0f);
			// p1
			glVertex3f(0.0f, 2.5f, -10.0f);
			// p2
			glVertex3f(-2.5f, 1.5f, -10.0f);
			// p3
			glVertex3f(0.0f, 1.5f, -10.0f);
		glEnd();


		glLineWidth(2.0f);
		/*
		GL_LINE_STRIP : line count == pt count -1; 
		p0->p1; p1->p2; p2-p3
		*/
		glBegin(GL_LINE_STRIP);
			// p0
			glColor4ub(255, 255, 255, 255);
			glVertex3f(0.5f, 2.5f, -10.0f);
			// p1
			glColor4ub(0, 255, 255, 255);
			glVertex3f(2.5f, 2.5f, -10.0f);
			// p3
			glColor4ub(0, 0, 255, 255);
			glVertex3f(0.5f, 1.5f, -10.0f);
			// p4
			glColor4ub(0, 0, 0, 255);
			glVertex3f(2.5f, 1.5f, -10.0f);
		glEnd();

		glColor4ub(0, 0, 255, 255);
		/*
		GL_LINE_LOOP : line count == pt count; 
		p0->p1; p1->p2; p2-p3, p3->p0
		*/
		glBegin(GL_LINE_LOOP);
			// p0
			glVertex3f(3.0f, 2.5f, -10.0f);
			// p1
			glVertex3f(5.0f, 2.5f, -10.0f);
			// p2
			glVertex3f(3.0f, 1.5f, -10.0f);
			// p3
			glVertex3f(5.0f, 1.5f, -10.0f);
		glEnd();
	}

	// draw triangle
	{
		/*
		GL_TRIANGLES : triangle count == (int)(pt count / 3); 
		p0->p1->p2;
		*/
		glBegin(GL_TRIANGLES);
			// p0
			glVertex3f(-5.0f, -1.0f + 0.5f, -10.f);
			// p1
			glVertex3f(-3.0f, -1.0f + 0.5f, -10.f);
			// p2
			glVertex3f(-5.0f, -2.5f + 0.5f, -10.f);
		glEnd();

		/*
		GL_TRIANGLE_STRIP : triangle count ; 
		p0->p1->p2;
		*/
		glBegin(GL_TRIANGLE_STRIP);
			// p0
			glColor4ub(255, 0, 0, 255);
			glVertex3f(-2.5f, -1.0f + 0.5f, -10.f);
			// p1
			glColor4ub(0, 255, 0, 255);
			glVertex3f(-0.5f, -1.0f + 0.5f, -10.f);
			// p2
			glColor4ub(0, 0, 255, 255);
			glVertex3f(-2.5f, -2.5f + 0.5f, -10.f);
		glEnd();

		/*
		GL_TRIANGLE_STRIP : triangle count ; 
		p0->p1->p2; p2->p1->p3;
		*/
		glBegin(GL_TRIANGLE_STRIP);
			// p0
			glColor4ub(255, 0, 0, 255);
			glVertex3f(0.0f, -1.0f + 0.5f, -10.f);
			// p1
			glColor4ub(0, 255, 0, 255);
			glVertex3f(2.0f, -1.0f + 0.5f, -10.f);
			// p2
			glColor4ub(0, 0, 255, 255);
			glVertex3f(0.0f, -2.5f + 0.5f, -10.f);
			// p3
			glColor4ub(255, 255, 255, 255);
			glVertex3f(2.0f, -2.5f + 0.5f, -10.f);
		glEnd();

		/*
		GL_TRIANGLE_FAN : triangle count ; 
		p0->p1->p2; p0->p2->p3; p0->p3->p4; p0->p4->p5;
		*/
		glBegin(GL_TRIANGLE_FAN);
			// p0
			glColor4ub(255, 255, 255, 255);
			glVertex3f(3.5f, -2.0f + 0.5f, -10.f);
			// p1
			glColor4ub(0, 0, 0, 255);
			glVertex3f(3.5f, -3.0f + 0.5f, -10.f);
			// p2
			glColor4ub(255, 0, 0, 255);
			glVertex3f(4.5f, -2.0f + 0.5f, -10.f);
			// p3
			glColor4ub(0, 255, 0, 255);
			glVertex3f(3.5f, -1.0f + 0.5f, -10.f);
			// p4
			glColor4ub(0, 0, 255, 255);
			glVertex3f(2.5f, -2.0f + 0.5f, -10.f);
			// p5
			glColor4ub(0, 0, 0, 255);
			glVertex3f(3.5f, -3.0f + 0.5f, -10.f);
		glEnd();
	}

	// draw QUAD
	{
		glColor4ub(0, 0, 255, 255);
		glBegin(GL_QUADS);
			glVertex3f(-5.0f, -3.0f, -10.0f);
			glVertex3f(-5.0f, -4.0f, -10.0f);
			glVertex3f(-3.0f, -4.0f, -10.0f);
			glVertex3f(-3.0f, -3.0f, -10.0f);
		glEnd();

		glColor4ub(0, 255, 0, 255);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(-2.5f, -3.0f, -10.0f);
			glVertex3f(-2.5f, -4.0f, -10.0f);
			glVertex3f(-1.0f, -4.0f, -10.0f);
			glVertex3f(-1.0f, -3.0f, -10.0f);
		glEnd();

	}

	// draw polygon
	{
		glColor4ub(255, 0, 0, 255);
		glBegin(GL_POLYGON);
			glVertex3f(-0.5f, -3.0f, -10.0f);
			glVertex3f(-0.5f, -4.0f, -10.0f);
			glVertex3f(1.5f, -4.0f, -10.0f);
			glVertex3f(1.5f, -3.0f, -10.0f);
		glEnd();

		glColor4ub(255, 255, 0, 255);
		glPolygonMode(GL_FRONT,GL_POINT);
		glPointSize(5.0f);
		glBegin(GL_POLYGON);
			glVertex3f(2.0f, -3.0f, -10.0f);
			glVertex3f(2.0f, -4.0f, -10.0f);
			glVertex3f(2.5f, -4.0f, -10.0f);
			glVertex3f(2.5f, -3.0f, -10.0f);
		glEnd();

		glColor4ub(0, 255, 255, 255);
		glPolygonMode(GL_FRONT,GL_LINE);
		glLineWidth(5.0f);
		glBegin(GL_POLYGON);
			glVertex3f(3.0f, -3.0f, -10.0f);
			glVertex3f(3.0f, -4.0f, -10.0f);
			glVertex3f(3.5f, -4.0f, -10.0f);
			glVertex3f(3.5f, -3.0f, -10.0f);

		glEnd();

		glColor4ub(255, 0, 255, 255);
		glPolygonMode(GL_FRONT,GL_FILL);
		glBegin(GL_POLYGON);
			glVertex3f(4.0f, -3.0f, -10.0f);
			glVertex3f(4.0f, -4.0f, -10.0f);
			glVertex3f(4.5f, -4.0f, -10.0f);
			glVertex3f(4.5f, -3.0f, -10.0f);
		glEnd();
	}
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