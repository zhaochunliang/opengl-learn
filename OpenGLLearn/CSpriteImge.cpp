#include "CSpriteImge.h"
#include "CTextureMgr.h"

CSpriteImage::CSpriteImage(CCamera& camera)
: mCamera(camera)
, mTranslatePos(0.0f, 0.0f, 0.0f)
{
	
}

CSpriteImage::~CSpriteImage()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mVBO);
}

void CSpriteImage::Init(const char* pfile)
{
	// init texture
	if (pfile != NULL)
	{
		mPTexture = CTextureMgr::CreateTexture(pfile);
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

}

void CSpriteImage::SetRect(float x, float y, float width, float height)
{
	float halfWidth  = width / 2.0f;
	float halfHeight = height/ 2.0f;

	mVertexts[0] = VertexNode(Vector3F(x - halfWidth, y - halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(0.0f,0.0f));
	mVertexts[1] = VertexNode(Vector3F(x + halfWidth, y - halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(1.0f,0.0f));
	mVertexts[2] = VertexNode(Vector3F(x + halfWidth, y + halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(1.0f,1.0f));
	mVertexts[3] = VertexNode(Vector3F(x - halfWidth, y + halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(0.0f,1.0f));

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNode) * 4, mVertexts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	static int Indexs[4] = {0, 1, 2, 3};
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 4, Indexs, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CSpriteImage::Draw()
{
	static float degree = 0.0f;
	glm::mat4 TranslateMat= glm::translate(glm::mat4(1.0f), glm::vec3(mTranslatePos.x, mTranslatePos.y, mTranslatePos.z));
	glm::mat4 RotateMat   = glm::rotate(glm::mat4(1.0), degree, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 ScaleMat    = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	glm::mat4 ModelMatrix = TranslateMat * RotateMat * ScaleMat; 

	glUseProgram(mProgram.mProgram);
	glUniformMatrix4fv(mProgram.GetLocation("M"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(mProgram.GetLocation("V"), 1, GL_FALSE, glm::value_ptr(mCamera.mViewMatrix));
	glUniformMatrix4fv(mProgram.GetLocation("P"), 1, GL_FALSE, glm::value_ptr(mCamera.mProjMatrix));

	// bind attribute data
	GLint posLoc       = mProgram.GetLocation("position");
	GLint normalLoc    = mProgram.GetLocation("normal");
	GLint textcoordLoc = mProgram.GetLocation("texcoord");

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc,      3, GL_FLOAT, GL_FALSE, sizeof(VertexNode), 0);
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc,   3, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(textcoordLoc);
	glVertexAttribPointer(textcoordLoc,2, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*6));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mPTexture->mTextureId);
	glUniform1i(mProgram.GetLocation("U_MTexture"), 0);


	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// to bind ibo and draw elements;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisable(GL_BLEND);

	glUseProgram(0);
}