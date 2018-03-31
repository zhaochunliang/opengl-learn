#include "CBoundaryLayer.h"
#include "CGISUtil.h"

CBoundaryLayer::CBoundaryLayer()
:mPPolygonVertexsBuf(NULL), mPPolygonBufSize(0)
{

}

CBoundaryLayer::~CBoundaryLayer()
{
	if (mPPolygonVertexsBuf != NULL )
	{
		free(mPPolygonVertexsBuf);
		mPPolygonVertexsBuf = NULL;
	}
}

void CBoundaryLayer::Init(const char* pGeoJson)
{
	CGeoJsonParser geojsonparser;
	geojsonparser.LoadGeoJsonContent(pGeoJson, mCountryInfoVec);

	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
}



void CBoundaryLayer::Bind(GLint posLoc, GLint normalLoc, GLint textcoordLoc)
{
	// bind attribute data
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc,      3, GL_FLOAT, GL_FALSE, sizeof(Vector3F), 0);
	//glEnableVertexAttribArray(normalLoc);
	//glVertexAttribPointer(normalLoc,   3, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*3));
	//glEnableVertexAttribArray(textcoordLoc);
	//glVertexAttribPointer(textcoordLoc,2, GL_FLOAT, GL_FALSE, sizeof(VertexNode), (void*)(sizeof(float)*6));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CBoundaryLayer::Draw()
{
	// to bind ibo and draw elements;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	for (unsigned int i=0; i< mCountryInfoVec.size(); ++i)
	{
		CountryInfo& bound = mCountryInfoVec[i];
		for (unsigned int j=0; j< bound.mCountryBoundary.size(); ++j)
		{
			TXPolygon& polygon = bound.mCountryBoundary[j];
			unsigned int VertexSize  = polygon.size();
			if (mPPolygonVertexsBuf == NULL)
			{
				mPPolygonVertexsBuf = (Vector3F*) malloc(sizeof(Vector3F) * VertexSize);
				memset(mPPolygonVertexsBuf, 0, sizeof(Vector3F) * VertexSize);
				mPPolygonBufSize    = VertexSize;
			}
			else if (VertexSize > mPPolygonBufSize)
			{
				mPPolygonVertexsBuf = (Vector3F*) realloc( mPPolygonVertexsBuf, sizeof(Vector3F) * VertexSize);
				memset(mPPolygonVertexsBuf, 0, sizeof(Vector3F) * VertexSize);
				mPPolygonBufSize    = VertexSize;
			}

			int*      pFaces   = new int[VertexSize];
			for (unsigned int ptidx = 0; ptidx < polygon.size(); ++ptidx)
			{
				double x =0, y=0, z=0;
				CGISUtil::getXYZWithDLonLat(polygon[ptidx].x, polygon[ptidx].y, x, y, z);
				mPPolygonVertexsBuf[ptidx].x = x;
				mPPolygonVertexsBuf[ptidx].y = y;
				mPPolygonVertexsBuf[ptidx].z = z;

				pFaces[ptidx] = ptidx;
			}

			glBindBuffer(GL_ARRAY_BUFFER, mVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3F) * VertexSize, mPPolygonVertexsBuf, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * VertexSize, pFaces, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			delete [] pFaces;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
			glDrawElements(GL_LINE_LOOP, VertexSize, GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
}