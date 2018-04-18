#ifndef OPENGL_LEARN_SPRITE_SHEET_H
#define OPENGL_LEARN_SPRITE_SHEET_H

#include <gl/glew.h>
#include "CCamera.h"
#include "CCommon.h"
#include "CTextureMgr.h"
#include "CGPUProgram.h"

class CSpriteSheet
{
public:
	CSpriteSheet(CCamera& camera);
	~CSpriteSheet();

public:
	void Init(const char* pPath);
	void SetRect(float x, float y, float width, float height);
	void Update(float deltaTime);
	void Draw();

public:
	CCamera&                    mCamera;
	GLuint                      mVBO, mIBO;
	CGPUProgram                 mProgram;
	CTexture**                  mPPTextures;
	VertexNode                  mVertexts[4];
	Vector3F                    mTranslatePos;

	int     mFrameCount;
	int     mFrameIndex;
	float   mFrameGAP;
	float   mTime;
};
#endif // OPENGL_LEARN_SPRITE_SHEET_H