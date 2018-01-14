#include "Util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char* loadFileContent(const char* fileName)
{
	FILE* pFile = fopen(fileName, "rb");
	if (pFile)
	{
		fseek(pFile,0,SEEK_END);
		int nLength = ftell(pFile);
		rewind(pFile);
		unsigned char* fileContent = (unsigned char*) malloc(sizeof(unsigned char) * (nLength + 1));
		if (fileContent)
		{
			memset(fileContent, 0, sizeof(unsigned char) * (nLength + 1));
			fread(fileContent, sizeof(unsigned char), nLength, pFile);
			fileContent[nLength] = '\0';
		}
		fclose(pFile);
		return fileContent;
	}
	return NULL;
}

unsigned char* loadBMP(unsigned char* pfileContent, int& width, int& height)
{
	width   = 0;
	height  = 0;
	if (pfileContent != NULL)
	{
		if (0x4D42 == *((unsigned short*)pfileContent))
		{
			int pixelDataoffset = *((int*)(pfileContent + 10));
			width  = *((int*)(pfileContent + 18));
			height = *((int*)(pfileContent + 22));
			unsigned char * pPixelData = pfileContent + pixelDataoffset;
			
			// convert BGR -> RGB
			const int pixelcount = width * height;
			for (int i = 0; i< pixelcount; ++i)
			{
				unsigned char B       = pPixelData[3 * i + 0];
				pPixelData[3 * i + 0] = pPixelData[3 * i + 2];
				pPixelData[3 * i + 2] = B;
			}
			return pPixelData;
		}
	}
	return NULL;
}