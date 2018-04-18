#include "CBoundaryLayer.h"
#include "CGISUtil.h"

CBoundaryLayer::CBoundaryLayer(CCamera& camera)
: mCamera(camera)
, mPPolygonVertexsBuf(NULL)
, mPPolygonBufSize(0)
{

}

CBoundaryLayer::~CBoundaryLayer()
{
	if (mPPolygonVertexsBuf != NULL )
	{
		free(mPPolygonVertexsBuf);
		mPPolygonVertexsBuf = NULL;
	}
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mVBO);
}

void CBoundaryLayer::Init(const char* pGeoJson)
{
	CGeoJsonParser geojsonparser;
	geojsonparser.LoadGeoJsonContent(pGeoJson, mCountryInfoVec);

	mProgram.AttatchShader(GL_VERTEX_SHADER,    "res/shaders/line.vs");
	mProgram.AttatchShader(GL_FRAGMENT_SHADER,  "res/shaders/line.fs");
	mProgram.Link();
	mProgram.DetectAttribute("position");
	mProgram.DetectUniform("line_color");
	mProgram.DetectUniform("M");
	mProgram.DetectUniform("V");
	mProgram.DetectUniform("P");


	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mIBO);
}

void CBoundaryLayer::Draw()
{
	static float degree = 0.0f;
	glm::mat4 TranslateMat= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 RotateMat   = glm::rotate(glm::mat4(1.0), degree, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 ScaleMat    = glm::scale(glm::mat4(1.0), glm::vec3(1.0));
	glm::mat4 ModelMatrix = TranslateMat * RotateMat * ScaleMat; 

	glUseProgram(mProgram.mProgram);
	glm::vec3 line_color(1.0f, 1.0f, 0.0f);
	glUniform3fv(mProgram.GetLocation("line_color"), 1, glm::value_ptr(line_color));
	glUniformMatrix4fv(mProgram.GetLocation("M"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(mProgram.GetLocation("V"), 1, GL_FALSE, glm::value_ptr(mCamera.mViewMatrix));
	glUniformMatrix4fv(mProgram.GetLocation("P"), 1, GL_FALSE, glm::value_ptr(mCamera.mProjMatrix));

	// bind attribute data
	GLuint posLoc = mProgram.GetLocation("position");
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glEnableVertexAttribArray(posLoc);
	glVertexAttribPointer(posLoc,      3, GL_FLOAT, GL_FALSE, sizeof(Vector3F), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// to bind ibo and draw elements;
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);
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
				mPPolygonVertexsBuf[ptidx].x = (float)x;
				mPPolygonVertexsBuf[ptidx].y = (float)y;
				mPPolygonVertexsBuf[ptidx].z = (float)z;

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
	glUseProgram(0);
}