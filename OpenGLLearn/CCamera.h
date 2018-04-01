#ifndef OPENGL_LEARN_CAMERA_H
#define OPENGL_LEARN_CAMERA_H

#include "CCommon.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

public:
	void Update(float deltaTime);
	void Pitch(float angle);
	void Yaw(float angle);

	void setViewport(const Vector4F &viewport);

	void lookAt(const Vector3F &eye, const Vector3F &center, const Vector3F &up);

	void perspective(float fovy, float aspect, float zNear, float zFar, const Vector2F& offset);


protected:
	void RotateView(float angle, float x, float y, float z);


public:
	Vector4F      mViewport;
	Vector3F      mEyePosition;
	Vector3F      mViewCenter;
	Vector3F      mUp;
	bool          mbMoveLeft, mbMoveRight;
	bool          mbMoveForward, mbMoveBackward;

	float         mfovy;                        //eye opened angle
	float         maspect;                      //ViewPortWidth/ViewPortHeight;
	float         mzNear, mzFar;                //the neareast and farest distance which eye can see;
	glm::mat4     mViewMatrix;
	glm::mat4     mProjMatrix;
};

#endif // OPENGL_LEARN_CAMERA_H