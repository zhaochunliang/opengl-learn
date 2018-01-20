#ifndef OPENGL_LEARN_UTIL_H
#define OPENGL_LEARN_UTIL_H

void  releaseFileContent(unsigned char* fileContent);
unsigned char* loadFileContent(const char* fileName);
unsigned char* loadBMP(unsigned char* pfileContent, int& width, int& height);

#endif