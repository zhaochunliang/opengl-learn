#include <Windows.h>
#include "CTexture.h"
#include "CGPUProgram.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

static unsigned int Pos_Left       = 10;
static unsigned int Pos_Top        = 10;
static unsigned int ViewPortWidth  = 800;
static unsigned int ViewPortHeight = 600;

CTexture     texture;
CGPUProgram program[3];
GLuint      VBO[3];

// An array of 3 vectors which represents 3 vertices
// [{coordinate},{coordinate},{coordinate}]
static const GLfloat g_vertex_buffer_data_0[] =
{
	-1.0f, -1.0f, 0.0f,
	 0.0f, -1.0f, 0.0f,
	-0.5f,  0.0f, 0.0f
};

// An array of 3 vectors which represents 3 vertices
// [{coordinate, color},{coordinate, color},{coordinate, color}]
static const GLfloat g_vertex_buffer_data_1[] = {
	0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
};

// An array of 3 vectors which represents 3 vertices
// [{coordinate, color, texcoord},{coordinate, color, texcoord},{coordinate, color, texcoord}]
static const GLfloat g_vertex_buffer_data_2[] = {
	-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
};

void init()
{
	glewInit();

	// init OpenGL
	glMatrixMode(GL_PROJECTION);
	GLdouble fovy   = 50.0f;                        //eye opened angle
	GLdouble aspect = ViewPortWidth/ViewPortHeight; //width / height
	GLdouble zNear  = 0.1f, zFar = 1000.0f;         //the neareast and farest distance which eye can see;
	gluPerspective(fovy, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.1f, 0.4f, 0.6f, 1.0f);

	texture.init("res/images/test.bmp");

	//to create three vertex buffer objects on GPU
	glGenBuffers(3, VBO);

	//to copy data from CPG to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_0), g_vertex_buffer_data_0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_1), g_vertex_buffer_data_1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_2), g_vertex_buffer_data_2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// to Organize Shader Program
	program[0].AttatchShader(GL_VERTEX_SHADER,    "res/shaders/simple_0.vs");
	program[0].AttatchShader(GL_FRAGMENT_SHADER,  "res/shaders/simple_0.fs");
	program[0].Link();
	program[0].DetectAttribute("pos");

	program[1].AttatchShader(GL_VERTEX_SHADER,    "res/shaders/simple_1.vs");
	program[1].AttatchShader(GL_FRAGMENT_SHADER,  "res/shaders/simple_1.fs");
	program[1].Link();
	program[1].DetectAttribute("pos");
	program[1].DetectAttribute("color");

	program[2].AttatchShader(GL_VERTEX_SHADER,    "res/shaders/simple_2.vs");
	program[2].AttatchShader(GL_FRAGMENT_SHADER,  "res/shaders/simple_2.fs");
	program[2].Link();
	program[2].DetectAttribute("pos");
	program[2].DetectAttribute("color");
	program[2].DetectAttribute("texcoord");
	program[2].DetectUniform("U_MainTexture");

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw simple triangle with shader program;
	glUseProgram(program[0].mProgram);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glEnableVertexAttribArray(program[0].GetLocation("pos"));
	glVertexAttribPointer(program[0].GetLocation("pos"), 3, GL_FLOAT, GL_FALSE, sizeof(float)* 3, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);

	glUseProgram(program[1].mProgram);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glEnableVertexAttribArray(program[1].GetLocation("pos"));
	glVertexAttribPointer(program[1].GetLocation("pos"),  3, GL_FLOAT, GL_FALSE, sizeof(float)* 7, 0);
	glEnableVertexAttribArray(program[1].GetLocation("color"));
	glVertexAttribPointer(program[1].GetLocation("color"),4, GL_FLOAT, GL_FALSE, sizeof(float)* 7, (void*)(sizeof(float)*3));
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);

	glUseProgram(program[2].mProgram);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glEnableVertexAttribArray(program[2].GetLocation("pos"));
	glVertexAttribPointer(program[2].GetLocation("pos"),      3, GL_FLOAT, GL_FALSE, sizeof(float)* 9, 0);
	glEnableVertexAttribArray(program[2].GetLocation("color"));
	glVertexAttribPointer(program[2].GetLocation("color"),    4, GL_FLOAT, GL_FALSE, sizeof(float)* 9, (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(program[2].GetLocation("texcoord"));
	glVertexAttribPointer(program[2].GetLocation("texcoord"), 2, GL_FLOAT, GL_FALSE, sizeof(float)* 9, (void*)(sizeof(float)*7));

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.mTextureId);
	glUniform1i(program[2].GetLocation("U_MainTexture"), 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
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