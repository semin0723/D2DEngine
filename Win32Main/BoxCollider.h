#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class BoxCollider : Component<BoxCollider>
{
public:
	BoxCollider() {}
	~BoxCollider() {}

	bool _isTrigger = false;
	float _left = 0;
	float _top = 0;
	float _right = 0;
	float _bottom = 0;
};

