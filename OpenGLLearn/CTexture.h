#ifndef OPENGL_LEARN_TEXTURE_H
#define OPENGL_LEARN_TEXTURE_H
#include <Windows.h>
#include <gl/glew.h>

#define GL_CLAMP_TO_EDGE 0x812F

class CTexture
{
public:
	void init(const char* fileName, bool invertY = true, GLenum wrapMode= GL_CLAMP_TO_EDGE);

public:
	GLuint mTextureId;
};


#endif