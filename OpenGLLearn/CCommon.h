#ifndef OPENGL_LEARN_COMMON_H
#define OPENGL_LEARN_COMMON_H

#include "Vector2.h"
#include "Vector3.h"

typedef Vector2<float>     Vector2F;
typedef Vector3<float>     Vector3F;
typedef Vector3<int>       Vector3I;

struct VertexNode
{
	Vector3F    position;
	Vector3F    normal;
	Vector2F    textcoord;
};


#endif // OPENGL_LEARN_COMMON_H