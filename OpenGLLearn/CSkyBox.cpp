#include "CSkyBox.h"
#include "CGlmLearn.h"

CSkyBox::CSkyBox(CCamera& camera)
: mCamera(camera)
{
	mImgNames[BoxFace_Top]       = "top.bmp";
	mImgNames[BoxFace_Bottom]    = "bottom.bmp";
	mImgNames[BoxFace_Left]      = "left.bmp";
	mImgNames[BoxFace_Right]     = "right.bmp";
	mImgNames[BoxFace_Front]     = "front.bmp";
	mImgNames[BoxFace_Back]      = "back.bmp";

	mBoxVertexs[BoxFace_Top][0]       = VertexNode(Vector3F(-1.0f, 1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 0.0f));
	mBoxVertexs[BoxFace_Top][1]       = VertexNode(Vector3F( 1.0f, 1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 0.0f));
	mBoxVertexs[BoxFace_Top][2]       = VertexNode(Vector3F( 1.0f, 1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 1.0f));
	mBoxVertexs[BoxFace_Top][3]       = VertexNode(Vector3F(-1.0f, 1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 1.0f));

	mBoxVertexs[BoxFace_Bottom][0]    = VertexNode(Vector3F(-1.0f,-1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 0.0f));
	mBoxVertexs[BoxFace_Bottom][1]    = VertexNode(Vector3F( 1.0f,-1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 0.0f));
	mBoxVertexs[BoxFace_Bottom][2]    = VertexNode(Vector3F( 1.0f,-1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 1.0f));
	mBoxVertexs[BoxFace_Bottom][3]    = VertexNode(Vector3F(-1.0f,-1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 1.0f));

	mBoxVertexs[BoxFace_Left][0]      = VertexNode(Vector3F(-1.0f,-1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 0.0f));
	mBoxVertexs[BoxFace_Left][1]      = VertexNode(Vector3F(-1.0f,-1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 0.0f));
	mBoxVertexs[BoxFace_Left][2]      = VertexNode(Vector3F(-1.0f, 1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 1.0f));
	mBoxVertexs[BoxFace_Left][3]      = VertexNode(Vector3F(-1.0f, 1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 1.0f));

	mBoxVertexs[BoxFace_Right][0]     = VertexNode(Vector3F( 1.0f,-1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 0.0f));
	mBoxVertexs[BoxFace_Right][1]     = VertexNode(Vector3F( 1.0f,-1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 0.0f));
	mBoxVertexs[BoxFace_Right][2]     = VertexNode(Vector3F( 1.0f, 1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 1.0f));
	mBoxVertexs[BoxFace_Right][3]     = VertexNode(Vector3F( 1.0f, 1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 1.0f));

	mBoxVertexs[BoxFace_Front][0]     = VertexNode(Vector3F(-1.0f,-1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 0.0f));
	mBoxVertexs[BoxFace_Front][1]     = VertexNode(Vector3F( 1.0f,-1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 0.0f));
	mBoxVertexs[BoxFace_Front][2]     = VertexNode(Vector3F( 1.0f, 1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 1.0f));
	mBoxVertexs[BoxFace_Front][3]     = VertexNode(Vector3F(-1.0f, 1.0f,-1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 1.0f));

	mBoxVertexs[BoxFace_Back][0]      = VertexNode(Vector3F( 1.0f,-1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 0.0f));
	mBoxVertexs[BoxFace_Back][1]      = VertexNode(Vector3F(-1.0f,-1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 0.0f));
	mBoxVertexs[BoxFace_Back][2]      = VertexNode(Vector3F(-1.0f, 1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(1.0f, 1.0f));
	mBoxVertexs[BoxFace_Back][3]      = VertexNode(Vector3F( 1.0f, 1.0f, 1.0f), Vector3F(0.0f,0.0f,0.0f), Vector2F(0.0f, 1.0f));

}

CSkyBox::~CSkyBox()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mIBO);
}

void CSkyBox::Init(const char* pPath)
{
	for (int i=0;i<BoxFace_Num; ++i)
	{
		std::string fullpath = pPath;
		fullpath = fullpath + "/";
		fullpath = fullpath + mImgNames[i];
		mTextures[i].init(fullpath.c_str());
	}

	// init shader program
	mProgram.AttatchShader(GL_VERTEX_SHADER,    "res/shaders/region_texture.vs");
	mProgram.AttatchShader(GL_FRAGMENT_SHADER,  "res/shaders/region_texture.fs");
	mProgram.Link();
	mProgram.DetectAttribute("position");
	mProgram.DetectAttribute("normal");
	mProgram.DetectAttribute("texcoord");
	mProgram.DetectUniform("M");
	mProgram.DetectUniform("V");
	mProgram.DetectUniform("P");
	mProgram.DetectUniform("U_MTexture");
	//mProgram.DetectUniform("U_WeatherTexture");

	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
}

void CSkyBox::Draw()
{
	static float degree = 0.0f;
	glm::mat4 TranslateMat= glm::translate(glm::mat4(1.0f), glm::vec3(mCamera.mEyePosition.x, mCamera.mEyePosition.y, mCamera.mEyePosition.z));
	glm::mat4 RotateMat   = glm::rotate(glm::mat4(1.0), degree, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 ScaleMat    = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	glm::mat4 ModelMatrix = TranslateMat * RotateMat * ScaleMat; 

	glUseProgram(mProgram.mProgram);
	glUniformMatrix4fv(mProgram.GetLocation("M"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(mProgram.GetLocation("V"), 1, GL_FALSE, glm::value_ptr(mCamera.mViewMatrix));
	glUniformMatrix4fv(mProgram.GetLocation("P"), 1, GL_FALSE, glm::value_ptr(mCamera.mProjMatrix));

	GLint posLoc       = mProgram.GetLocation("position");
	GLint normalLoc    = mProgram.GetLocation("normal");
	GLint textcoordLoc = mProgram.GetLocation("texcoord");

	// bind attribute data
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc,      3, GL_FLOAT, GL_FALSE, sizeof(VertexNode), 0);
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc,   3, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(textcoordLoc);
	glVertexAttribPointer(textcoordLoc,2, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*6));
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glEnable(GL_TEXTURE_2D);
	const unsigned int VertexCount  = 4;
	static int pFaces[VertexCount] = {0, 1, 2, 3};
	for (int faceIndex = 0; faceIndex < BoxFace_Num; ++faceIndex)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNode) * VertexCount, &(mBoxVertexs[faceIndex]), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * VertexCount, pFaces, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTextures[faceIndex].mTextureId);
		glUniform1i(mProgram.GetLocation("U_MTexture"), 0);

		// to bind ibo and draw elements;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
		glDrawElements(GL_QUADS, VertexCount, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	
	glUseProgram(0);
}