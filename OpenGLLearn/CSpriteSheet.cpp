#include "CSpriteSheet.h"
#include "Soil/SOIL.h"
#include "Json/cJSON.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct Sprite
{
	std::string filename;
	Vector4I    frame;
};

CSpriteSheet::CSpriteSheet(CCamera& camera)
: mCamera(camera)
, mTranslatePos(0.0f, 0.0f, 0.0f)
{

}

CSpriteSheet::~CSpriteSheet()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mVBO);

	for (int i = 0; i< mFrameCount; ++i)
	{
		CTexture* pTexture= mPPTextures[i];
		delete pTexture;
		pTexture = NULL;
	}
	delete []mPPTextures;
}

void CSpriteSheet::Init(const char* pPath)
{
	int startFrame = 31, endFrame = 240, framePerSecond = 30;
	mFrameGAP             = 1.0f / framePerSecond;
	mFrameCount           = endFrame - startFrame + 1;
	mPPTextures            = new CTexture*[mFrameCount];
	mFrameIndex           = 0;

	std::string jsonfile = pPath;
	jsonfile = jsonfile + "/spritesheet.json";
	std::ifstream src_json_file(jsonfile.c_str(), ios::in);
	if (!src_json_file.good())
	{
		return ;
	}

	std::map<std::string, Sprite> spriteMap;
	std::stringstream buffer;  
	buffer << src_json_file.rdbuf();  
	std::string contents(buffer.str());
	cJSON *json = cJSON_Parse(contents.c_str());
	if (json)
	{
		cJSON* jsonChild      = json->child;
		if (jsonChild)
		{
			string strKey(jsonChild->string);
			if (strKey == "frames")
			{
				cJSON* jsonsprites = jsonChild->child;
				while(jsonsprites)
				{
					Sprite sprite;
					cJSON* jsonsprite = jsonsprites->child;
					while(jsonsprite)
					{
						string spritestrkey = jsonsprite->string;
						if (spritestrkey == "filename")
						{
							sprite.filename = jsonsprite->valuestring;
						}
						else if (spritestrkey == "frame")
						{
							cJSON* pJson = jsonsprite->child;
							while(pJson)
							{
								std::string str = pJson->string;
								if(str=="x")
								{
									sprite.frame.left = pJson->valueint;
								}
								else if (str=="y")
								{
									sprite.frame.top = pJson->valueint;
								}
								else if (str=="w")
								{
									sprite.frame.width = pJson->valueint;
								}
								else if (str=="h")
								{
									sprite.frame.height = pJson->valueint;
								}
								pJson = pJson->next;
							}
						}
						jsonsprite = jsonsprite->next;
					}
					spriteMap.insert(std::make_pair<std::string, Sprite>(sprite.filename, sprite));
					jsonsprites = jsonsprites->next;
				}
			}
		}
		cJSON_Delete(json);
	}


	std::string pngfile = pPath;
	pngfile = pngfile + "/spritesheet.png";
	int width = 0, height = 0, channels= 0, forcechannels=SOIL_LOAD_AUTO;
	unsigned char* img = SOIL_load_image(pngfile.c_str(), &width, &height, &channels,forcechannels);
	if (img)
	{
		// std::cout<<width << height << std::endl;
		// init texture
		char szBuffer[256] = { '\0' };
		for (int i = startFrame; i <= endFrame; ++i)
		{
			memset(szBuffer, 0, 256);
			strcpy(szBuffer, "");
			strcat(szBuffer, "a");

			if (i<10)
			{
				char temp[32] = {0};
				sprintf(temp,"000%d",i);
				strcat(szBuffer, temp);
			}
			else if (i>=10&&i<100)
			{
				char temp[32] = { 0 };
				sprintf(temp, "00%d", i);
				strcat(szBuffer, temp);
			}
			else if (i >= 100 && i < 1000)
			{
				char temp[32] = { 0 };
				sprintf(temp, "0%d", i);
				strcat(szBuffer, temp);
			}
			else if (i >= 1000)
			{
				char temp[32] = { 0 };
				sprintf(temp, "%d", i);
				strcat(szBuffer, temp);
			}
			strcat(szBuffer, ".png");
			std::map<std::string, Sprite>::iterator it = spriteMap.find(szBuffer);
			if (it != spriteMap.end())
			{
				Sprite& sprite = it->second;
				// std::cout<< sprite.filename << ", (" << sprite.frame.left << "," << sprite.frame.top << "," << sprite.frame.width << "," << sprite.frame.height << ")"<< std::endl;
				mPPTextures[i - startFrame] = new CTexture;

				unsigned int* imgBigBuffer = (unsigned int*) img;
				unsigned int* imgSubBuffer = new unsigned int[sprite.frame.width * sprite.frame.height];
				for (int y = 0; y < sprite.frame.height; ++y)
				{
					for (int x = 0; x < sprite.frame.width; ++x)
					{
						int offsetposfrom = (sprite.frame.top + y) * width + (sprite.frame.left + x);
						int offsetposto   = sprite.frame.width * y + x;
						imgSubBuffer[offsetposto]   = imgBigBuffer[offsetposfrom];
					}
				}
				//SOIL_save_image(szBuffer, SOIL_SAVE_TYPE_BMP ,sprite.frame.width, sprite.frame.height, channels, (unsigned char *)imgSubBuffer);
				mPPTextures[i - startFrame]->mTextureId = SOIL_create_OGL_texture((unsigned char *)imgSubBuffer, sprite.frame.width, sprite.frame.height, 4, 0, SOIL_FLAG_POWER_OF_TWO);
				delete [] imgSubBuffer;

				//mPPTextures[i - startFrame]->init(sprite.filename.c_str());
			}
		}
		SOIL_free_image_data(img);
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

	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
}

void CSpriteSheet::SetRect(float x, float y, float width, float height)
{
	float halfWidth  = width / 2.0f;
	float halfHeight = height/ 2.0f;

	mVertexts[0] = VertexNode(Vector3F(x - halfWidth, y - halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(0.0f,0.0f));
	mVertexts[1] = VertexNode(Vector3F(x + halfWidth, y - halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(1.0f,0.0f));
	mVertexts[2] = VertexNode(Vector3F(x + halfWidth, y + halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(1.0f,1.0f));
	mVertexts[3] = VertexNode(Vector3F(x - halfWidth, y + halfHeight, 0.0f), Vector3F(0.0f, 0.0f, 0.0f), Vector2F(0.0f,1.0f));


	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNode) * 4, mVertexts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	static int Indexs[4] = {0, 1, 2, 3};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 4, Indexs, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void CSpriteSheet::Update(float deltaTime)
{
	mTime += deltaTime;
	if (mTime > mFrameGAP)
	{
		mTime = 0.0f;
		++mFrameIndex;
		if (mFrameIndex >= mFrameCount)
		{
			mFrameIndex = 0;
		}
	}
}

void CSpriteSheet::Draw()
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
	glBindTexture(GL_TEXTURE_2D,  mPPTextures[mFrameIndex]->mTextureId);
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