#include "CTexture.h"
#include "Util.h"

#include "Soil/SOIL.h"

#define  TEXTURE_SOIL

void CTexture::init(const char* fileName, bool invertY /*= true */, GLenum wrapMode /*= GL_CLAMP_TO_EDGE*/)
{
#ifdef  TEXTURE_SOIL

	unsigned int flags = SOIL_FLAG_POWER_OF_TWO;
	if (invertY)
	{
		flags |= SOIL_FLAG_INVERT_Y;
	}
	mTextureId = SOIL_load_OGL_texture(fileName, 0, 0, flags);
	if (wrapMode==GL_CLAMP_TO_EDGE)
	{
		glBindTexture(GL_TEXTURE_2D, mTextureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

#else

	unsigned char * pFileContent = loadFileContent(fileName);
	if (pFileContent != NULL)
	{
		int width = 0, height = 0;
		unsigned char* pPixelData = loadBMP(pFileContent, width, height);
		if (pPixelData != NULL && width > 0 && height >0)
		{
			glGenTextures(1, &mTextureId);
			glBindTexture(GL_TEXTURE_2D, mTextureId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pPixelData);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		free(pFileContent);
		pFileContent = NULL;
	}

#endif
}