#include "CTexture.h"
#include "Util.h"


void CTexture::init(const char* fileName)
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
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pPixelData);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		free(pFileContent);
		pFileContent = NULL;
	}
}