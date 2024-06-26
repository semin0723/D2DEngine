#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector3 size) : _calculatedBorderPos(4)
{
	_borderPos.push_back(D2D1::Point2F(0.0f, 0.0f));
	_borderPos.push_back(D2D1::Point2F(size.x, 0.0f));
	_borderPos.push_back(D2D1::Point2F(size.x, size.y));
	_borderPos.push_back(D2D1::Point2F(0.0f, size.y));
}

void BoxCollider::SetBorderLocation(D2D1::Matrix3x2F transform)
{
	for (int i = 0; i < _borderPos.size(); i++) {
		_calculatedBorderPos[i] = _borderPos[i] * transform;
	}
}
