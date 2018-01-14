#ifndef OPENGL_LEARN_VERTOR3
#define OPENGL_LEARN_VERTOR3

#include <math.h>

template<typename T>
class Vector3
{
public:
	Vector3();
	Vector3(T x, T y, T z);

public:
	Vector3 operator*(float scaler);
	Vector3 operator+(Vector3& r);
	Vector3 operator-(Vector3& r);
	Vector3 operator^(Vector3& r);
	void operator=(Vector3 &r);
	float operator*(Vector3 &r);
	void Normalize();
	float Magnitude();

public:
	union {
		struct 
		{
			T x,y,z;
		};

		T v[3];
	};
};

// Note: the define of class template must be put in same file
template<typename T>
Vector3<T>::Vector3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}


template<typename T>
Vector3<T>::Vector3(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<typename T>
Vector3<T> Vector3<T>::operator*(float scaler)
{
	return Vector3<T>(this->x * scaler, this->y * scaler, this->z * scaler);
}

template<typename T>
Vector3<T> Vector3<T>::operator+(Vector3<T>& r)
{
	return Vector3<T>(this->x + r.x, this->y + r.y, this->z + r.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(Vector3<T>& r)
{
	return Vector3<T>(this->x - r.x, this->y - r.y, this->z - r.z);
}

template<typename T>
Vector3<T> Vector3<T>::operator^(Vector3<T>& r)
{
	return Vector3<T>(y*r.z-z*r.y,x*r.z-z*r.z,x*r.y-y*r.x);
}

template<typename T>
void Vector3<T>::operator=(Vector3<T> &r)
{
	this->x = r.x;
	this->y = r.y;
	this->z = r.z;
}

template<typename T>
float Vector3<T>::operator*(Vector3<T>& r)
{
	return this->x*r.x+ this->y *r.y+ this->z *r.z;
}

template<typename T>
void Vector3<T>::Normalize()
{
	float len = Magnitude();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}

template<typename T>
float Vector3<T>::Magnitude()
{
	return sqrtf(x*x+y*y+z*z);
}


#endif
