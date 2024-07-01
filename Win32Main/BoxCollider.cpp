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
	float minX = FLT_MIN;
	float maxX = FLT_MIN;
	float minY = FLT_MAX;
	float maxY = FLT_MAX;
	for (int i = 0; i < _borderPos.size(); i++) {
		_calculatedBorderPos[i] = _borderPos[i] * transform;
		minX = (std::min)(_calculatedBorderPos[i].x, minX);
		minY = (std::min)(_calculatedBorderPos[i].y, minX);
		maxX = (std::max)(_calculatedBorderPos[i].x, maxX);
		maxY = (std::max)(_calculatedBorderPos[i].y, maxY);
	}
	_bounds = { minX, minY, maxX, maxY };
}
