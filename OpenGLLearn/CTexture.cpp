#include "CTexture.h"
#include "Util.h"
#include "Soil/SOIL.h"
#include <math.h>

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

void CParticleTexture::init(int width, int height)
{
	// RGBA Image
	const int  imageBufferSize = width * height * 4;
	unsigned char* pImageBuffer = new unsigned char[imageBufferSize];
	
	float maxDist2Center = sqrtf(width * width + height * height) / 2.0f;
	float centerX = width  / 2.0f;
	float centerY = height / 2.0f;
	for (int x=0; x < width; ++x)
	{
		for (int y=0; y < height; ++y)
		{
			float deltaX(x - centerX);
			float deltaY(y - centerY);
			float dist2Center = sqrtf(deltaX * deltaX + deltaY * deltaY);
			float alpha  = powf(1.0f - (dist2Center / maxDist2Center), 8.0f);
			alpha = alpha > 1.0f ? 1.0f : alpha;

			int curOffset = (x * width + y) * 4;
			pImageBuffer[curOffset  + 0]    = 255;
			pImageBuffer[curOffset  + 1]    = 255;
			pImageBuffer[curOffset  + 2]    = 255;
			pImageBuffer[curOffset  + 3]    = (unsigned char)(alpha*255.0f);

		}
	}

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	// set parameter for current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, pImageBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	delete pImageBuffer;
}