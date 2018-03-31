#ifndef OPENGL_LEARN_OBJ_MODEL_H
#define OPENGL_LEARN_OBJ_MODEL_H

#include <gl/glew.h>
#include "CCommon.h"

class CObjModel
{
public:
	bool LoadModel(const char* pModelFile);
	void Bind(GLint posLoc, GLint normalLoc, GLint textcoordLoc);
	void Draw();

public:
	GLuint             mVBO, mIBO;
	unsigned int       mIndexCount;
};
#endif