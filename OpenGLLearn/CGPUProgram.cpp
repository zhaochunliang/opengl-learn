#include "CGPUProgram.h"
#include "Util.h"
#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>

void CGPUProgram::AttatchShader(GLenum shaderType, const char* pShaderFile)
{
	unsigned char* pShaderCodeStr = loadFileContent(pShaderFile);
	if (pShaderCodeStr != NULL)
	{
		const GLchar* pShaderCode = (GLchar*)(pShaderCodeStr);
		GLuint shader = glCreateShader(shaderType);
		glShaderSource( shader, 1, &pShaderCode, NULL );
		free(pShaderCodeStr);
		pShaderCodeStr = NULL;
		
		glCompileShader( shader );
		GLint compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
		if (!compiled )
		{
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

			GLchar* log = new GLchar[len+1];
			glGetShaderInfoLog( shader, len, &len, log );
			printf("failed to glCompileShader: %s.\n ", log);
			delete [] log;
#endif 
		}
		mAttatchedShaders.push_back(shader);
	}
}

void CGPUProgram::Link()
{
	mProgram = glCreateProgram();
	for (std::vector<GLuint>::iterator it = mAttatchedShaders.begin(); it != mAttatchedShaders.end(); ++it)
	{
		glAttachShader(mProgram, *it);
	}

	glLinkProgram( mProgram );
	
	GLint linked;
	glGetProgramiv( mProgram, GL_LINK_STATUS, &linked );
	if (!linked )
	{
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv( mProgram, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( mProgram, len, &len, log );
		printf("failed to glLinkProgram: %s.\n ", log);
		delete [] log;
#endif
		for (std::vector<GLuint>::iterator it = mAttatchedShaders.begin(); it != mAttatchedShaders.end(); ++it)
		{
			glDetachShader(mProgram, *it);
		}

		mAttatchedShaders.clear();
		mProgram = 0;

	}
}

void CGPUProgram::DetectAttribute(const char* pAttributeName)
{
	GLint loc  = glGetAttribLocation(mProgram, pAttributeName);
	if (loc != -1)
	{
		if (mLocations.find(pAttributeName) == mLocations.end())
		{
			mLocations.insert(std::make_pair<std::string, GLint>(pAttributeName,loc));
		}
	}
}

void CGPUProgram::DetectUniform(const char* pUniformName)
{
	GLint loc  = glGetUniformLocation(mProgram, pUniformName);
	if (loc != -1)
	{
		if (mLocations.find(pUniformName) == mLocations.end())
		{
			mLocations.insert(std::make_pair<std::string, GLint>(pUniformName,loc));
		}
	}
}

GLint CGPUProgram::GetLocation(const char* pName)
{
	if (mLocations.find(pName) == mLocations.end())
	{
		return -1;
	}

	return mLocations[pName];
}

void CGPUProgram::CreateProgram(const char* pVertextShaderCode, const char* pFramShaderCode)
{
	mProgram = glCreateProgram();
	const GLchar* pVertextCode = NULL;
	const GLchar* pFramCode    = NULL;
	unsigned char* pVertextCodeStr = loadFileContent(pVertextShaderCode);
	unsigned char* pFramCodeStr    = loadFileContent(pFramShaderCode);
	if (pVertextCodeStr != NULL)
	{
		pVertextCode = (GLchar*)(pVertextCodeStr);
		GLuint shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource( shader, 1, &pVertextCode, NULL );
		free(pVertextCodeStr);
		pVertextCodeStr = NULL;

		glCompileShader( shader );
		GLint compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
		if (!compiled )
		{
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

			GLchar* log = new GLchar[len+1];
			glGetShaderInfoLog( shader, len, &len, log );
			printf("failed to glCompileShader: %s.\n ", log);
			delete [] log;
#endif 
		}

		glAttachShader(mProgram, shader);
	}

	if (pFramCodeStr != NULL)
	{
		pFramCode    = (GLchar*)(pFramCodeStr);
		GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource( shader, 1, &pFramCode, NULL );
		free(pFramCodeStr);
		pFramCodeStr = NULL;

		glCompileShader( shader );
		GLint compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
		if (!compiled )
		{
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

			GLchar* log = new GLchar[len+1];
			glGetShaderInfoLog( shader, len, &len, log );
			printf("failed to glCompileShader: %s.\n ", log);
			delete [] log;
#endif 
		}

		glAttachShader(mProgram, shader);
	}

	glLinkProgram( mProgram );
	GLint linked;
	glGetProgramiv( mProgram, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv( mProgram, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( mProgram, len, &len, log );
		printf("failed to glLinkProgram: %s.\n ", log);
		delete [] log;
#endif

}

}