#ifndef OPENGL_LEARN_PARTICAL_SYSTEM_H
#define OPENGL_LEARN_PARTICAL_SYSTEM_H

#include "CSpriteImge.h"

class CPartical:public CSpriteImage
{
public:
	CPartical(CCamera& camera, int viewPortWidth, int viewPortHeight);
	~CPartical();

public:
	void Update(float deltaTime);

private:
	Vector3F                 mInitedPos;
	Vector3F                 mCurPos;
	float                    mLiftTime;
	float                    mExistTime;
};

class CParticalSystem
{
public:
	CParticalSystem(CCamera& camera);
	~CParticalSystem();

public:
	void Init(int viewPortWidth, int viewPortHeight, int count);
	void Update(float deltaTime);
	void Draw();

private:
	void releaseReourses();

private:
	CCamera&                    mCamera;
	CTexture*                   mPTexture;
	std::vector<CPartical*>     mParticalVec;
};

#endif // OPENGL_LEARN_PARTICAL_SYSTEM_H