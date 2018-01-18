#ifndef OPENGL_LEARN_SKYBOX
#define OPENGL_LEARN_SKYBOX

#include "CTexture.h"
#include "Vector3.h"

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
	CSkyBox();
	~CSkyBox();

public:
	void init(const char* pImgsPath);
	void Draw(float x, float y, float z);

public:
	// the vertex position of six faces;
	static Vector3<float> BoxVertexs[BoxFace_Num][4];

	// the texture of six faces
	CTexture  mTextures[BoxFace_Num];

	// the texture name of six faces
	char     mImgNames[BoxFace_Num][100];

	// the start index of display list
	GLuint   mDisplayStartIndex;
	GLubyte  mDisplayIds[BoxFace_Num];

};
#endif
