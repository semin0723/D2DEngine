#include "Transform.h"

Transform::Transform() : _position{ 0, 0, 0 }, _scale{ 1, 1, 1 }, _rotate{ 0, 0, 0 }
{

}

Transform::Transform(Vector3 pos, Vector3 scale, Vector3 rot) : _position(pos), _scale(scale), _rotate(rot)
{
}

D2D1_MATRIX_3X2_F Transform::GetTransform()
{
	return D2D1::Matrix3x2F::Scale(D2D1::SizeF(_scale.x, _scale.y)) *
		D2D1::Matrix3x2F::Translation(_position.x, _position.y) *
		D2D1::Matrix3x2F::Rotation(_rotate.z, D2D1::Point2F(_position.x, _position.y))
		;  
}
