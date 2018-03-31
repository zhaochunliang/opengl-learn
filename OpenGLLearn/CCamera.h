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

protected:
	void RotateView(float angle, float x, float y, float z);


public:
	Vector3F      mPosition;
	Vector3F      mViewCenter;
	Vector3F      mUp;
	bool          mbMoveLeft, mbMoveRight;
	bool          mbMoveForward, mbMoveBackward;
};

#endif // OPENGL_LEARN_CAMERA_H