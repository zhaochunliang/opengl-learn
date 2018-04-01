#ifndef OPENGL_LEARN_BoundaryLayer_H
#define OPENGL_LEARN_BoundaryLayer_H

#include <gl/glew.h>
#include "CCamera.h"
#include "CGeoJsonParser.h"
#include "CGPUProgram.h"


class CBoundaryLayer
{
public:
	CBoundaryLayer(CCamera& camera);
	~CBoundaryLayer();

public:
	void Init(const char* pGeoJson);
	void Draw();

private:
	CCamera&                    mCamera;
    std::vector<CountryInfo>    mCountryInfoVec;
	GLuint                      mVBO, mIBO;
	Vector3F*                   mPPolygonVertexsBuf;
	GLuint                      mPPolygonBufSize;
	CGPUProgram                 mProgram;
};

#endif // OPENGL_LEARN_BoundaryLayer_H