#ifndef OPENGL_LEARN_COMMON_H
#define OPENGL_LEARN_COMMON_H

#include "Glm/glm.hpp"
#include "Glm/ext.hpp"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


typedef Vector2<int>       Vector2I;
typedef Vector3<int>       Vector3I;
typedef Vector4<int>       Vector4I;
typedef Vector2<float>     Vector2F;
typedef Vector3<float>     Vector3F;
typedef Vector4<float>     Vector4F;

struct VertexNode
{
	VertexNode(){}
	VertexNode(Vector3F position_, Vector3F normal_, Vector2F textcoord_): position(position_), normal(normal_), textcoord(textcoord_){}
	Vector3F    position;
	Vector3F    normal;
	Vector2F    textcoord;
};


#endif // OPENGL_LEARN_COMMON_H