#ifndef OPENGL_LEARN_BoundaryLayer_H
#define OPENGL_LEARN_BoundaryLayer_H

#include <gl/glew.h>
#include "CGeoJsonParser.h"


class CBoundaryLayer
{
public:
	CBoundaryLayer();
	~CBoundaryLayer();

public:
	void Init(const char* pGeoJson);
	void Bind(GLint posLoc, GLint normalLoc, GLint textcoordLoc);
	void Draw();

private:
    std::vector<CountryInfo>    mCountryInfoVec;
	GLuint                      mVBO, mIBO;
	Vector3F*                   mPPolygonVertexsBuf;
	GLuint                      mPPolygonBufSize;
};

#endif // OPENGL_LEARN_BoundaryLayer_H