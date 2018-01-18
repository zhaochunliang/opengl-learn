#include "CSkyBox.h"
#include "Vector3.h"
#include <string.h>

Vector3<float> CSkyBox::BoxVertexs[BoxFace_Num][4] = {
	{ Vector3<float>(-1.0f, 1.0f, -1.0f), Vector3<float>(1.0f, 1.0f, -1.0f), Vector3<float>(1.0f, 1.0f, 1.0f), Vector3<float>(-1.0f, 1.0f, 1.0f)},      // top
	{ Vector3<float>(-1.0f, -1.0f, 1.0f), Vector3<float>(1.0f, -1.0f, 1.0f), Vector3<float>(1.0f, -1.0f, -1.0f), Vector3<float>(-1.0f, -1.0f, -1.0f)},  // bottom
	{ Vector3<float>(-1.0f, -1.0f, 1.0f), Vector3<float>(-1.0f, -1.0f, -1.0f), Vector3<float>(-1.0f, 1.0f, -1.0f), Vector3<float>(-1.0f, 1.0f, 1.0f)},  // left
	{ Vector3<float>(1.0f, -1.0f, -1.0f), Vector3<float>(1.0f, -1.0f, 1.0f), Vector3<float>(1.0f, 1.0f, 1.0f), Vector3<float>(1.0f, 1.0f, -1.0f)},      // right
	{ Vector3<float>(-1.0f, -1.0f, -1.0f), Vector3<float>(1.0f, -1.0f, -1.0f), Vector3<float>(1.0f, 1.0f, -1.0f), Vector3<float>(-1.0f, 1.0f, -1.0f)},  // font
	{ Vector3<float>(1.0f, -1.0f, 1.0f), Vector3<float>(-1.0f, -1.0f, 1.0f), Vector3<float>(-1.0f, 1.0f, 1.0f), Vector3<float>(1.0f, 1.0f, 1.0f)},      // back
};

CSkyBox::CSkyBox()
: mDisplayStartIndex(0)
{
	strcpy(mImgNames[BoxFace_Top],     "top.bmp");
	strcpy(mImgNames[BoxFace_Bottom],  "bottom.bmp");
	strcpy(mImgNames[BoxFace_Left],    "left.bmp");
	strcpy(mImgNames[BoxFace_Right],   "right.bmp");
	strcpy(mImgNames[BoxFace_Front],   "front.bmp");
	strcpy(mImgNames[BoxFace_Back],    "back.bmp");
}

CSkyBox::~CSkyBox()
{
	if (mDisplayStartIndex > 0)
	{
		glDeleteLists(mDisplayStartIndex, BoxFace_Num);
	}
}
void CSkyBox::init(const char* pImgsPath)
{
	char temp[256] = {0};

	for (int i=0;i<BoxFace_Num; ++i)
	{
		strcpy(temp,pImgsPath);
		strcat(temp,"/");
		strcat(temp,mImgNames[i]);
		mTextures[i].init(temp);
	}

	// malloc display list id
	mDisplayStartIndex = glGenLists(BoxFace_Num);
	for (int i = 0; i < BoxFace_Num; ++i)
	{
		// create display list
		mDisplayIds[i] =  mDisplayStartIndex + i;
		glNewList(mDisplayIds[i], GL_COMPILE);

		glBindTexture(GL_TEXTURE_2D, mTextures[i].mTextureId);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(BoxVertexs[i][0].x, BoxVertexs[i][0].y, BoxVertexs[i][0].z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(BoxVertexs[i][1].x, BoxVertexs[i][1].y, BoxVertexs[i][1].z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(BoxVertexs[i][2].x, BoxVertexs[i][2].y, BoxVertexs[i][2].z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(BoxVertexs[i][3].x, BoxVertexs[i][3].y, BoxVertexs[i][3].z);
		glEnd();

		glEndList();
	}

}

void CSkyBox::Draw(float x, float y, float z)
{

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
	glTranslatef(x,y,z);
	glColor4ub(255, 255, 255, 255);
	glEnable(GL_TEXTURE_2D);

	if (mDisplayStartIndex > 0)
	{
		// call display lists;
		glListBase(0);
		glCallLists(BoxFace_Num,GL_UNSIGNED_BYTE, mDisplayIds);
	}
	else
	{
		for (int i = 0; i < BoxFace_Num; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, mTextures[i].mTextureId);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(BoxVertexs[i][0].x, BoxVertexs[i][0].y, BoxVertexs[i][0].z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(BoxVertexs[i][1].x, BoxVertexs[i][1].y, BoxVertexs[i][1].z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(BoxVertexs[i][2].x, BoxVertexs[i][2].y, BoxVertexs[i][2].z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(BoxVertexs[i][3].x, BoxVertexs[i][3].y, BoxVertexs[i][3].z);
			glEnd();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	glPopMatrix();
}

