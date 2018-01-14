#include "CObjModel.h"
#include "Util.h"
#include <windows.h>
#include <gl/GL.h>
#include <string>
#include <sstream>
#include <vector>

void CObjModel::Init(const char* pObjFile)
{
	struct FloatData
	{
		float v[3];
	};
	
	struct VertexDefine
	{
		int postinIndex;
		int texturIndex;
		int normalIndex;
	};
	std::vector<FloatData>    positions, texcoords, normals;
	std::vector<VertexDefine> vertexes;
	std::vector<int>          indexes;

	unsigned char* filecontent = loadFileContent(pObjFile);
	std::stringstream ssFileContent((char*)filecontent);
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		if(strlen(szOneLine) > 0)
		{
			if (szOneLine[0] == 'v')
			{
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);

					printf("texture coordinate:%f,%f \n", floatData.v[0], floatData.v[1]);
				}
				else if (szOneLine[1] == 'n')
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);

					printf("normal coordinate:%f,%f,%f \n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
				else
				{
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);

					printf("position coordinate:%f,%f,%f \n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
			}
			else if (szOneLine[0] == 'f')
			{
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexStr; // pos_index/texture_index/nomal_index
				printf("face: %s \n", szOneLine);
				for (int i=0; i<3; ++i)
				{
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);

					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texIndexStr = vertexStr.substr(pos + 1, pos2 - pos -1);

					std::string nomalIndexStr= vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);

					VertexDefine vd;
					vd.postinIndex = atoi(posIndexStr.c_str());
					vd.texturIndex = atoi(texIndexStr.c_str());
					vd.normalIndex = atoi(nomalIndexStr.c_str());
					
					printf("%d,%d,%d\n",vd.postinIndex,vd.texturIndex,vd.normalIndex);

					int nCurrentVertexIndex = -1;
					int nCurrentVertexCount = (int) vertexes.size();
					for (int j=0;j<nCurrentVertexCount; ++j)
					{
						if (vertexes[j].postinIndex == vd.postinIndex &&
							vertexes[j].texturIndex == vd.texturIndex &&
							vertexes[j].normalIndex == vd.normalIndex)
						{
							nCurrentVertexIndex = j;
							break;
						}
					}
					if (nCurrentVertexIndex == -1)
					{
						nCurrentVertexIndex = (int) vertexes.size();
						vertexes.push_back(vd);
					}
					indexes.push_back(nCurrentVertexIndex);
				}
			}
		}
	}

	printf("unique vertex count %u index count %u\n",vertexes.size(),indexes.size());
	mIndicesCount = (int) indexes.size();
	mIndices = new int[mIndicesCount];

	for (int i=0; i< mIndicesCount; ++i)
	{
		mIndices[i] = indexes[i];
	}

	int vertexcount = (int)vertexes.size();
	mVertexes = new VertexData[vertexcount];
	for (int i=0;i<vertexcount; ++i)
	{
		memcpy(mVertexes[i].position, positions[vertexes[i].postinIndex -1].v, sizeof(float) * 3);
		memcpy(mVertexes[i].texcood,  texcoords[vertexes[i].texturIndex -1].v, sizeof(float) * 2);
		memcpy(mVertexes[i].normal,   normals[vertexes[i].normalIndex -1].v, sizeof(float) * 3);
	}

	free(filecontent);
}

void CObjModel::Draw()
{
	static float angle = 0.0f;
	angle += 0.02f;
	if (angle>=360.0f)
	{
		angle = 0.0f;
	}

	//glDisable(GL_TEXTURE_2D);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();
	glTranslatef(0.0f,0.0f,-3.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (int i=0; i<mIndicesCount; ++i)
	{
		glTexCoord2fv(mVertexes[mIndices[i]].texcood);
		glNormal3fv(mVertexes[mIndices[i]].normal);
		glVertex3fv(mVertexes[mIndices[i]].position);
	}
	glEnd();
	glPopMatrix();
}

