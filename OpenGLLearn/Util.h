#ifndef OPENGL_LEARN_UTIL_H
#define OPENGL_LEARN_UTIL_H


float randf();//0.0~1.0
float srandf();//-1.0~1.0

void  releaseFileContent(unsigned char* fileContent);
unsigned char* loadFileContent(const char* fileName);
unsigned char* loadBMP(unsigned char* pfileContent, int& width, int& height);

#endif