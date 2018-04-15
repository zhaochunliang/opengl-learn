#ifndef OPENGL_LEARN_VERTOR4
#define OPENGL_LEARN_VERTOR4

#include <math.h>

template<typename T>
class Vector4
{
public:
	Vector4();
	Vector4(T x, T y, T z);
	Vector4(T x, T y, T z, T w);

public:
	Vector4 operator*(float scaler);
	Vector4 operator+(Vector4& r);
	Vector4 operator-(Vector4& r);
	Vector4 operator^(Vector4& r);
	void operator=(const Vector4 &r);
	float operator*(Vector4 &r);
	void Normalize();
	float Magnitude();
	
	bool operator==(const Vector4 &r);

public:
	union {
		struct 
		{
			T x,y,z,w;
		};

		struct 
		{
			T left,top,right,bottom;
		};

		T v[4];
	};
};

// Note: the define of class template must be put in same file
template<typename T>
Vector4<T>::Vector4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 1;
}

template<typename T>
Vector4<T>::Vector4(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}

template<typename T>
Vector4<T>::Vector4(T x, T y, T z, T w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template<typename T>
Vector4<T> Vector4<T>::operator*(float scaler)
{
	return Vector4<T>(this->x * scaler, this->y * scaler, this->z * scaler);
}

template<typename T>
Vector4<T> Vector4<T>::operator+(Vector4<T>& r)
{
	return Vector4<T>(this->x + r.x, this->y + r.y, this->z + r.z);
}

template<typename T>
Vector4<T> Vector4<T>::operator-(Vector4<T>& r)
{
	return Vector4<T>(this->x - r.x, this->y - r.y, this->z - r.z);
}

template<typename T>
Vector4<T> Vector4<T>::operator^(Vector4<T>& r)
{
	return Vector4<T>(y*r.z-z*r.y,x*r.z-z*r.z,x*r.y-y*r.x);
}

template<typename T>
void Vector4<T>::operator=(const Vector4<T> &r)
{
	this->x = r.x;
	this->y = r.y;
	this->z = r.z;
	this->w = r.w;
}

template<typename T>
float Vector4<T>::operator*(Vector4<T>& r)
{
	return this->x*r.x+ this->y *r.y+ this->z *r.z;
}

template<typename T>
void Vector4<T>::Normalize()
{
	float len = Magnitude();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}

template<typename T>
float Vector4<T>::Magnitude()
{
	return sqrtf(x*x+y*y+z*z);
}

template<typename T>
bool Vector4<T>::operator==(const Vector4<T> &r)
{
	return this->x == r.x && this->y == r.y && this->z == r.z && this->w == r.w;
}
#endif
