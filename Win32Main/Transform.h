#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class Transform : public Component<Transform>
{
public:
	Transform();
	Transform(Vector3 pos, Vector3 scale, Vector3 rot);
	~Transform() {}

	void SetRectSize(Vector3& size) { _rectSize = size; }
	D2D1::Matrix3x2F GetTransform();

	Vector3 _position;
	Vector3 _scale;
	Vector3 _rotate;
	Vector3 _rectSize;
};