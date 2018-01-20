#include "CObjModel.h"
#include "Util.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;


bool CObjModel::LoadModel(const char* pModelFile)
{
	// to load obj model content
	char* pModelContent = (char*)loadFileContent(pModelFile);
	if (pModelFile != NULL)
	{
		// to decode obj model content
		//printf("%s. \n", pModelContent);
		stringstream ssModelContent(pModelContent);
		char lineStr[256];

		vector<Vector3F>   tempPostions;
		vector<Vector3F>   tempNormals;
		vector<Vector2F>   tempTextcoords;
		vector<Vector3I>   tempVertexIndexs;
		vector<int>        faces; 

		while(!ssModelContent.eof())
		{
			ssModelContent.getline(lineStr, 256);
			if (strlen(lineStr) > 0)
			{
				stringstream ssOneLine(lineStr);
				string             tempFlagStr;
				//printf("Line: %s. \n", ssLineStr);
				if (lineStr[0] == 'v')
				{
					if (lineStr[1] == 't')
					{
						Vector2F textcoord;
						ssOneLine >> tempFlagStr;
						ssOneLine >> textcoord.x;
						ssOneLine >> textcoord.y;
						tempTextcoords.push_back(textcoord);

						//printf("textcoord: %f, %f. \n", textcoord.x, textcoord.y);
					}
					else if (lineStr[1] == 'n')
					{
						Vector3F normal;
						ssOneLine >> tempFlagStr;
						ssOneLine >> normal.x;
						ssOneLine >> normal.y;
						ssOneLine >> normal.z;
						tempNormals.push_back(normal);

						//printf("normal: %f, %f, %f. \n", normal.x, normal.y, normal.z);
					}
					else
					{
						Vector3F position;
						ssOneLine >> tempFlagStr;
						ssOneLine >> position.x;
						ssOneLine >> position.y;
						ssOneLine >> position.z;
						tempPostions.push_back(position);

						//printf("position: %f, %f, %f. \n", position.x, position.y, position.z);
					}
				}
				else if (lineStr[0] == 'f')
				{
					ssOneLine >> tempFlagStr;
					string vertexStr, vpStr, vtStr, vnStr;
					//printf("face: %s. \n", lineStr);
					for (int i = 0; i < 3; ++i)
					{
						// 1/1/1
						ssOneLine >> vertexStr;
						size_t vp_vt = vertexStr.find_first_of('/');
						size_t vt_vn = vertexStr.find_last_of('/');
						vpStr = vertexStr.substr(0, vp_vt);
						vtStr = vertexStr.substr(vp_vt + 1, vt_vn - vp_vt - 1);
						vnStr = vertexStr.substr(vt_vn + 1, vertexStr.length() - vt_vn - 1);

						Vector3I vertexIndex;
						vertexIndex.v[0] = atoi(vpStr.c_str()) - 1;
						vertexIndex.v[1] = atoi(vnStr.c_str()) - 1;
						vertexIndex.v[2] = atoi(vtStr.c_str()) - 1;
						
						int curVertexIndex = -1;
						for (int vertexIdx = 0; vertexIdx < tempVertexIndexs.size(); ++vertexIdx)
						{
							if (vertexIndex == tempVertexIndexs[vertexIdx])
							{
								curVertexIndex = vertexIdx;
								break;
							}
						}
						
						if (curVertexIndex == -1)
						{
							curVertexIndex  = tempVertexIndexs.size();
							tempVertexIndexs.push_back(vertexIndex);
						}

						faces.push_back(curVertexIndex);
					}
				}
			}
		}
		//printf("face count: %u. \n", faces.size() / 3);
		releaseFileContent((unsigned char*)pModelContent);

		// to organize vertex data;
		unsigned int       mnVertexNodeCount = tempVertexIndexs.size();
		VertexNode*        mpVertexNodes = new VertexNode[mnVertexNodeCount];
		for (int i = 0; i < mnVertexNodeCount; ++i)
		{
			Vector3I& VertexIndex = tempVertexIndexs[i];
			memcpy(&mpVertexNodes[i].postion,   &tempPostions[VertexIndex.v[0]],    sizeof(Vector3F));
			memcpy(&mpVertexNodes[i].normal,    &tempNormals[VertexIndex.v[1]],     sizeof(Vector3F));
			memcpy(&mpVertexNodes[i].textcoord, &tempTextcoords[VertexIndex.v[2]],  sizeof(Vector2F));
		}

		// to generate vertex buffer obj
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNode) * mnVertexNodeCount, mpVertexNodes, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		delete [] mpVertexNodes;

		mIndexCount = (unsigned int)faces.size();
		unsigned int* pIndexs = new unsigned int[mIndexCount];
		for (int i = 0; i < mIndexCount; ++i)
		{
			pIndexs [i] = faces[i];
		}

		// to generate index buffer obj
		glGenBuffers(1, &mIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndexCount, pIndexs, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		delete [] pIndexs;

		return true;
	}

	return false;
}

void CObjModel::Bind(GLint posLoc, GLint normalLoc, GLint textcoordLoc)
{
	// bind attribute data
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc,      3, GL_FLOAT, GL_FALSE, sizeof(VertexNode), 0);
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc,   3, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*3));
	glEnableVertexAttribArray(textcoordLoc);
	glVertexAttribPointer(textcoordLoc,2, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*6));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CObjModel::Draw()
{
	// to bind ibo and draw elements;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}