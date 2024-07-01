#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class BoxCollider : public Component<BoxCollider>
{
public:
	BoxCollider(Vector3 size);
	~BoxCollider() {}

	void SetTrigger(const bool state) { _isTrigger = state; }
	void SetBorderLocation(D2D1::Matrix3x2F transform);

	bool _isTrigger = false;
	D2D1_RECT_F _bounds;
	std::vector<D2D1_POINT_2F> _borderPos;
	std::vector<D2D1_POINT_2F> _calculatedBorderPos;
};

