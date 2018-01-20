#ifndef OPENGL_LEARN_OBJ_MODEL_H
#define OPENGL_LEARN_OBJ_MODEL_H

#include <gl/glew.h>
#include "Vector2.h"
#include "Vector3.h"

typedef Vector2<float>     Vector2F;
typedef Vector3<float>     Vector3F;
typedef Vector3<int>       Vector3I;

struct VertexNode 
{
	Vector3F   postion;
	Vector3F   normal;
	Vector2F   textcoord;
};

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