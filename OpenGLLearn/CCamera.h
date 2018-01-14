#ifndef OPENGL_LEARN_CAMERA
#define OPENGL_LEARN_CAMERA

#include "Vector3.h"

class CCamera
{
public:
	typedef Vector3<float>  Vector3f;

public:
	CCamera();

public:
	void Update(float deltaTime);
	void Pitch(float angle);
	void Yaw(float angle);

protected:
	void RotateView(float angle, float x, float y, float z);

public:
	Vector3f         mPosition;
	Vector3f         mViewCenter;
	Vector3f         mUp;
	bool             mbMoveLeft, mbMoveRight;
	bool             mbMoveForward,mbMoveBackward;
};

#endif
