#ifndef OPENGL_LEARN_SKYBOX_H
#define OPENGL_LEARN_SKYBOX_H
#include "CCamera.h"
#include "CCommon.h"
#include "CTexture.h"
#include "CGPUProgram.h"
#include <string>
#include <vector>

using namespace std;

class CSkyBox
{
public:
	enum BoxFace
	{
		BoxFace_Top        = 0,
		BoxFace_Bottom     = 1,
		BoxFace_Left       = 2,
		BoxFace_Right      = 3,
		BoxFace_Front      = 4,
		BoxFace_Back       = 5,
		BoxFace_Num        = 6
	};

public:
	CSkyBox(CCamera& camera);
	~CSkyBox();

public:
	void Init(const char* pPath);
	void Draw();

public:
	CCamera&           mCamera;
	VertexNode         mBoxVertexs[BoxFace_Num][4];  // the vertex position of six faces;   
	CTexture           mTextures[BoxFace_Num]; 	    // the texture of six faces
	string             mImgNames[BoxFace_Num];       // the texture name of six faces

	GLuint             mVBO, mIBO;
	CGPUProgram        mProgram;
};
#endif // OPENGL_LEARN_SKYBOX_H