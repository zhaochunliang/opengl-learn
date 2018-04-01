#ifndef OPENGL_LEARN_SPHERE_H
#define OPENGL_LEARN_SPHERE_H

#include <gl/glew.h>
#include "CCamera.h"
#include "CCommon.h"
#include "CTexture.h"
#include "CGPUProgram.h"

class CSphere
{
public:
	CSphere(CCamera& camera);
	~CSphere();

public:
	void Init(const char* pTexturefile);
	void Draw();

private:
	CCamera&           mCamera;
	unsigned int       mLongitudeBands;
	unsigned int       mLatitudeBands;
	CTexture           mTextures[2];
	GLuint             mVBO, mIBO;
	unsigned int       mIndexCount;
	CGPUProgram        mProgram;
};

#endif // OPENGL_LEARN_SPHERE_H