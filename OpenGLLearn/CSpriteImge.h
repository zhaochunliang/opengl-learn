#ifndef OPENGL_LEARN_SPRITE_IMAGE_H
#define OPENGL_LEARN_SPRITE_IMAGE_H

#include <gl/glew.h>
#include "CCamera.h"
#include "CCommon.h"
#include "CTextureMgr.h"
#include "CGPUProgram.h"

class CSpriteImage
{
public:
	CSpriteImage(CCamera& camera);
	~CSpriteImage();

public:
	void Init(const char* pfile);
	void SetRect(float x, float y, float width, float height);
	void Draw();

public:
	CCamera&                    mCamera;
	GLuint                      mVBO, mIBO;
	CGPUProgram                 mProgram;
	CTexture*                   mPTexture;
	VertexNode                  mVertexts[4];
	Vector3F                    mTranslatePos;
};
#endif // OPENGL_LEARN_SPRITE_IMAGE_H