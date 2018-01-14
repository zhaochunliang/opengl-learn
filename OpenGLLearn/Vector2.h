#ifndef OPENGL_LEARN_VERTOR2
#define OPENGL_LEARN_VERTOR2

#include <math.h>

template<typename T>
class Vector2
{
public:
	Vector2();
	Vector2(T x, T y);

public:
	Vector2 operator*(float scaler);
	Vector2 operator+(Vector2& r);
	Vector2 operator-(Vector2& r);
	Vector2 operator^(Vector2& r);
	void operator=(Vector2 &r);
	float operator*(Vector2 &r);
	void Normalize();
	float Magnitude();

public:
	union {
		struct 
		{
			T x,y;
		};

		T v[2];
	};
};

// Note: the define of class template must be put in same file
template<typename T>
Vector2<T>::Vector2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}


template<typename T>
Vector2<T>::Vector2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(float scaler)
{
	return Vector2<T>(this->x * scaler, this->y * scaler);
}

template<typename T>
Vector2<T> Vector2<T>::operator+(Vector2<T>& r)
{
	return Vector2<T>(this->x + r.x, this->y + r.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(Vector2<T>& r)
{
	return Vector2<T>(this->x - r.x, this->y - r.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator^(Vector2<T>& r)
{
	return Vector2<T>(r.x, r.y);
}

template<typename T>
void Vector2<T>::operator=(Vector2<T> &r)
{
	this->x = r.x;
	this->y = r.y;
}

template<typename T>
float Vector2<T>::operator*(Vector2<T>& r)
{
	return this->x*r.x+ this->y *r.y;
}

template<typename T>
void Vector2<T>::Normalize()
{
	float len = Magnitude();
	this->x /= len;
	this->y /= len;
}

template<typename T>
float Vector2<T>::Magnitude()
{
	return sqrtf(x*x+y*y);
}


#endif
