#pragma once
#include <d2d1_1helper.h>

class Vector3 : public D2D1_VECTOR_3F{
public:
	//float _x;
	//float _y;
	//float _z;
	Vector3();
	Vector3(float x, float y, float z);

	const float Magnitude() const;
	Vector3 Normalized() const;

	void operator=	(const Vector3& v);

	Vector3 operator+=	(const Vector3& v);
	Vector3 operator-=	(const Vector3& v);
	Vector3 operator*=	(const float& scalar);
	Vector3 operator/=	(const float& scalar);

	Vector3 operator+	(const Vector3& v) const;
	Vector3 operator-	(const Vector3& v) const;
	Vector3 operator*	(const float& scalar) const;
	Vector3 operator/	(const float& scalar) const;

	bool operator==		(const Vector3& v) const;
};

const float dot(Vector3& a, Vector3& b);
Vector3 Cross(Vector3& a, Vector3& b);