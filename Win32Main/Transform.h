#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class Transform : public Component<Transform>
{
public:
	Transform();
	Transform(Vector3 pos, Vector3 scale, Vector3 rot);
	~Transform() {}

	Vector3 _position;
	Vector3 _scale;
	Vector3 _rotate;
};