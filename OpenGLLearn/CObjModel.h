#ifndef OPENGL_LEARN_OBJMODEL
#define OPENGL_LEARN_OBJMODEL

#include "VertexData.h"

class CObjModel
{
public:
	void Init(const char* pObjFile);
	void Draw();


public:
	VertexData*    mVertexes;
	int*           mIndices;
	int            mIndicesCount;
};

#endif
