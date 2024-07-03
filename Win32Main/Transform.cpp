#include "Transform.h"

Transform::Transform() : _position{ 0, 0, 0 }, _scale{ 1, 1, 1 }, _rotate{ 0, 0, 0 }, _normal{ 0, -1, 0 }
{

}

Transform::Transform(Vector3 pos, Vector3 scale, Vector3 rot) : _position(pos), _scale(scale), _rotate(rot), _normal{ 0, -1, 0 }
{
}

D2D1::Matrix3x2F Transform::GetTransform()
{
	return D2D1::Matrix3x2F::Scale(D2D1::SizeF(_scale.x, _scale.y), D2D1::Point2F(_rectSize.x / 2.0f, _rectSize.y / 2.0f)) *
		D2D1::Matrix3x2F::Rotation(_rotate.z, D2D1::Point2F(_rectSize.x / 2.0f, _rectSize.y / 2.0f)) * 
		D2D1::Matrix3x2F::Translation(_position.x, _position.y)
		;  
}

void Transform::CalcRotation(Vector3& movedir)
{
	Vector3 normalDir = movedir.Normalized();
	float cosValue = dot(_normal, normalDir);
	float angle = acosf(cosValue) * (180 / M_PI);
	Vector3 crossVector = Cross(_normal, normalDir);
	_normal = normalDir;
	if (crossVector.z < 0) {
		_rotate -= Vector3(0, 0, angle);
	}
	else {
		_rotate += Vector3(0, 0, angle);
	}
}
