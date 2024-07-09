#pragma once
#include "ECSElements.h"
#include "globalheader.h"


class UITransform : public Component<UITransform>
{
public:
	UITransform() {}
	UITransform(Vector3 pos, Vector3 scale, Vector3 rotate);
	~UITransform() {}
	
	void UpdatePosition();
	const Vector3 GetScreenPosition() const;
	const Vector3& GetRectSize() const { return _size; }
	// Position On Screen
	Vector3 _position;
	Vector3 _scale;
	Vector3 _rotate;
	Vector3 _size;
	
	D2D1::Matrix3x2F _relativeTransform;
	D2D1::Matrix3x2F _screenTransform;
};

