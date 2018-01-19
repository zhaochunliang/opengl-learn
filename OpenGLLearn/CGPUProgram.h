#ifndef OPENGL_LEARN_GPU_PROGRAM_H
#define OPENGL_LEARN_GPU_PROGRAM_H

#include <gl/glew.h>
#include <string>
#include <vector>
#include <map>

class CGPUProgram
{
public:
	void AttatchShader(GLenum shaderType, const char* pShaderFile);
	void Link();

	void DetectAttribute(const char* pAttributeName);
	void DetectUniform(const char* pUniformName);
	GLint GetLocation(const char* pName);

	void CreateProgram(const char* pVertextShaderCode, const char* pFramShaderCode);

public:
	GLuint  mProgram;

private:
	std::map<std::string, GLint>   mLocations;
	std::vector<GLuint>            mAttatchedShaders;
};

#endif