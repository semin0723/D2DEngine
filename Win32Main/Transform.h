#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class Transform : public Component<Transform>
{
public:
	Transform();
	Transform(Vector3 pos, Vector3 scale, Vector3 rot);
	~Transform() {}

	D2D1_MATRIX_3X2_F GetTransform();

	Vector3 _position;
	Vector3 _scale;
	Vector3 _rotate;
};