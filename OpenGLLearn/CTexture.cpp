#include "CTexture.h"
#include "Util.h"


void CTexture::init(const char* fileName, bool invertY /*= true */, GLenum wrapMode /*= GL_CLAMP_TO_EDGE*/)
{
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
}