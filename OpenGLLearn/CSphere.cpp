#include "CSphere.h"
#include <math.h>
#include <vector>

using namespace std;

#define M_PI 3.14159265358979323846 

CSphere::CSphere()
:mLongitudeBands(50), mLatitudeBands(50)
{

}

CSphere::~CSphere()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mVBO);
}

void CSphere::Init(const char* pTexturefile)
{
	unsigned int VertexSize  = (mLatitudeBands + 1) * (mLongitudeBands + 1);
	unsigned int VertexIndex = 0;
	VertexNode* pVertexs = new VertexNode[VertexSize];
	memset(pVertexs, 0, sizeof(VertexNode) * VertexSize);
	for (unsigned int latNum = 0; latNum <= mLatitudeBands; latNum++)
	{
		float lat    = (float)(M_PI /2 - latNum * M_PI / mLatitudeBands);      //纬度范围[PI/2,-PI/2]
		float sinLat = sin(lat);   
		float cosLat = cos(lat);
	
		for (unsigned int lonNum = 0; lonNum <= mLongitudeBands; lonNum++)
		{
			float lon = (float)(lonNum * 2 * M_PI / mLongitudeBands - M_PI); //经度范围[-PI到 PI]
			float sinLon = sin(lon);       
			float cosLon = cos(lon);
			
			float x = cosLat * sinLon;
			float y = sinLat;
			float z = cosLat * cosLon;

			float u =    ((float)lonNum / mLongitudeBands);
			float v = 1- ((float)latNum / mLatitudeBands);

			pVertexs[VertexIndex].position.x = x;
			pVertexs[VertexIndex].position.y = y;
			pVertexs[VertexIndex].position.z = z;

			pVertexs[VertexIndex].normal.x = x;
			pVertexs[VertexIndex].normal.y = y;
			pVertexs[VertexIndex].normal.z = z;

			pVertexs[VertexIndex].textcoord.x = u;
			pVertexs[VertexIndex].textcoord.y = v;
			VertexIndex++;
		}
	}

	unsigned int FaceSize  = (mLatitudeBands) * (mLongitudeBands) * 2;
	Vector3I* pFaces = new Vector3I[FaceSize];
	memset(pFaces, 0, sizeof(Vector3I) * FaceSize);
	mIndexCount = FaceSize * 3;
	unsigned int FaceIndex = 0;
	for (unsigned int latNum = 0; latNum < mLatitudeBands; latNum++)
	{
		for (unsigned int lonNum = 0; lonNum < mLongitudeBands; lonNum++)
		{
			unsigned int PTSizeEachRow = mLongitudeBands + 1;
			unsigned int first         = latNum * PTSizeEachRow + lonNum;
			unsigned int second        = first + PTSizeEachRow;
			
			pFaces[FaceIndex].v[0]    = first;
			pFaces[FaceIndex].v[1]    = second;
			pFaces[FaceIndex].v[2]    = first + 1;
			FaceIndex++;

			pFaces[FaceIndex].v[0]    = second;
			pFaces[FaceIndex].v[1]    = second + 1;
			pFaces[FaceIndex].v[2]    = first  + 1;
			FaceIndex++;
		}
	}
	

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNode) * VertexSize, pVertexs, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete [] pVertexs;

	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3I) * FaceSize, pFaces, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete [] pFaces;

}



void CSphere::Bind(GLint posLoc, GLint normalLoc, GLint textcoordLoc)
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

void CSphere::Draw()
{
	// to bind ibo and draw elements;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT_FACE);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPopMatrix();
}