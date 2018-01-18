#include "CEarth.h"

#define GL_CLAMP_TO_EDGE 0x812F

void CEarth::init(const char* pObjFile, const char* pTextureFile)
{
	mObjModule.Init(pObjFile);
	mTexture.init(pTextureFile, GL_CLAMP_TO_EDGE);
}

void CEarth::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture.mTextureId);
	mObjModule.Draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}