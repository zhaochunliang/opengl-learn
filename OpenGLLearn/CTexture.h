#ifndef OPENGL_LEARN_TEXTURE_H
#define OPENGL_LEARN_TEXTURE_H
#include <Windows.h>
#include <gl/glew.h>

class CTexture
{
public:
	void init(const char* fileName);

public:
	GLuint mTextureId;
};


#endif