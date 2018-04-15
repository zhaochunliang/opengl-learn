#ifndef OPENGL_LEARN_TEXTURE_MGR_H
#define OPENGL_LEARN_TEXTURE_MGR_H

#include "CTexture.h"
#include <map>

class CTextureMgr
{
public:
	static CTexture* CreateTexture(const char* fileName, bool invertY = true, GLenum wrapMode= GL_CLAMP_TO_EDGE);
	static void ClearCachedTextures();

private:
	static std::map<const char*, CTexture*> mCachedTextures;
};
#endif // OPENGL_LEARN_TEXTURE_MGR_H