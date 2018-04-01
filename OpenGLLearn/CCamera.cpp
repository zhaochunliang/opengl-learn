#include "CCamera.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

CCamera::CCamera()
: mEyePosition(0.0f, 0.0f, 0.0f)
, mViewCenter(0.0f, 0.0f, -1.0f)
, mUp(0.0f,1.0f,0.0f)
, mbMoveLeft(false)
, mbMoveRight(false)
, mbMoveForward(false)
, mbMoveBackward(false)
, mfovy(45.0f)
, maspect(1.2f)
, mzNear(0.1f)
, mzFar(1000.0f)
{
	mViewMatrix = glm::lookAt(glm::vec3(mEyePosition.x, mEyePosition.y, mEyePosition.z), glm::vec3(mViewCenter.x, mViewCenter.y, mViewCenter.z), glm::vec3(mUp.x, mUp.y, mUp.z));
	mProjMatrix = glm::perspective<float>(mfovy, maspect, mzNear, mzFar);

}

CCamera::~CCamera()
{

}

void CCamera::RotateView(float angle, float x, float y, float z)
{
	Vector3F viewDirection = mViewCenter - mEyePosition;
	Vector3F newDirection;
	float C = cosf(angle);
	float S = sinf(angle);

	Vector3F tempX(C+x*x*(1-C),x*y*(1-C)-z*S,x*z*(1-C)+y*S);
	newDirection.x = tempX*viewDirection;

	Vector3F tempY(x*y*(1-C)+z*S, C+y*y*(1-C), y*z*(1-C)-x*S);
	newDirection.y = tempY*viewDirection;

	Vector3F tempZ(x*z*(1 - C) - y*S,y*z*(1 - C)+x*S, C + z*z*(1-C));
	newDirection.z = tempZ*viewDirection;

	mViewCenter = mEyePosition + newDirection;
}


void CCamera::Update(float deltaTime)
{
	//update everything
	static float movespeed = 1.0f ;
	static float rotatespeed = 1.0f;

	if (mbMoveLeft)
	{
		//mPosition.x -= movespeed * deltaTime;
		//mViewCenter.x -= movespeed*deltaTime;

		/*
		Vector3f leftDirection(-1.0f,0.0f,0.0f);
		leftDirection.Normalize();
		mPosition = mPosition + leftDirection * movespeed * deltaTime;
		mViewCenter = mViewCenter + leftDirection * movespeed * deltaTime;
		*/

		//left direction vector
		RotateView(rotatespeed*deltaTime, 0.0f, 1.0f, 0.0f);
	}

	if (mbMoveRight)
	{
		//mPosition.x += movespeed * deltaTime;
		//mViewCenter.x += movespeed*deltaTime;
		
		/*
		Vector3f rightDirection(1.0f,0.0f,0.0f);
		rightDirection.Normalize();
		mPosition = mPosition + rightDirection * movespeed * deltaTime;
		mViewCenter = mViewCenter + rightDirection * movespeed * deltaTime;
		*/

		//right direction vector
		RotateView(-rotatespeed*deltaTime, 0.0f, 1.0f, 0.0f);
	}

	if (mbMoveForward)
	{
		//mPosition.z -= movespeed * deltaTime;
		//mViewCenter.z -= movespeed*deltaTime;

		Vector3F forwardDirection(0.0f, 0.0f, -1.0f);
		forwardDirection.Normalize();
		mEyePosition   = mEyePosition   + forwardDirection * movespeed * deltaTime;
		mViewCenter = mViewCenter + forwardDirection * movespeed * deltaTime;
	}

	if (mbMoveBackward)
	{
		//mPosition.z += movespeed * deltaTime;
		//mViewCenter.z += movespeed*deltaTime;

		Vector3F backwardDirection(0.0f, 0.0f, 1.0f);
		backwardDirection.Normalize();
		mEyePosition   = mEyePosition   + backwardDirection * movespeed * deltaTime;
		mViewCenter = mViewCenter + backwardDirection * movespeed * deltaTime;
	}

	//set model view matrix
	mViewMatrix = glm::lookAt(glm::vec3(mEyePosition.x, mEyePosition.y, mEyePosition.z), glm::vec3(mViewCenter.x, mViewCenter.y, mViewCenter.z), glm::vec3(mUp.x, mUp.y, mUp.z));
}

void CCamera::Pitch(float angle)
{
	//right direction vector
	Vector3F viewDirection = mViewCenter - mEyePosition;
	viewDirection.Normalize();
	Vector3F rightDirection = viewDirection ^ mUp;
	rightDirection.Normalize();
	RotateView(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}

void CCamera::Yaw(float angle)
{
	RotateView(angle, mUp.x, mUp.y, mUp.z);
}

void CCamera::setViewport(const Vector4F &viewport)
{
	if (mViewport == viewport)
	{
		return;
	}

	mViewport = viewport;
}

void CCamera::lookAt(const Vector3F &eye, const Vector3F &center, const Vector3F &up)
{
	mEyePosition  = eye;
	mViewCenter   = center;
	mUp           = up;
	mViewMatrix = glm::lookAt(glm::vec3(mEyePosition.x, mEyePosition.y, mEyePosition.z), glm::vec3(mViewCenter.x, mViewCenter.y, mViewCenter.z), glm::vec3(mUp.x, mUp.y, mUp.z));
	
}

void CCamera::perspective(float fovy, float aspect, float zNear, float zFar, const Vector2F& offset)
{
	mfovy       = fovy;
	maspect     = aspect;
	mzNear      = zNear;
	mzFar       = zFar;
	mProjMatrix = glm::perspective<float>(mfovy, maspect, mzNear, mzFar);
}