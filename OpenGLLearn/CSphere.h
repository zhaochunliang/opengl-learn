#ifndef OPENGL_LEARN_SPHERE_H
#define OPENGL_LEARN_SPHERE_H

#include <gl/glew.h>
#include "CCommon.h"


class CSphere
{
public:
	CSphere();
	~CSphere();

public:
	void Init(const char* pTexturefile);
	void Bind(GLint posLoc, GLint normalLoc, GLint textcoordLoc);
	void Draw();

private:
	unsigned int       mLongitudeBands;
	unsigned int       mLatitudeBands;
	
	GLuint             mVBO, mIBO;
	unsigned int       mIndexCount;
};

#endif // OPENGL_LEARN_SPHERE_H