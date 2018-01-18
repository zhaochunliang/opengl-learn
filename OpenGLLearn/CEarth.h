#ifndef OPENGL_LEARN_EARTH
#define OPENGL_LEARN_EARTH

#include "CObjModel.h"
#include "CTexture.h"

class CEarth
{
public:
	void init(const char* pObjFile, const char* pTextureFile);
	void Draw();

private:
	CObjModel mObjModule;
	CTexture  mTexture;
};

#endif