#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class Camera
{
public:
	Camera() { UpdateCameraTransform(); }
	~Camera() {}

	D2D1_POINT_2F _cameraPosition = { 0, 0 };
	D2D1_POINT_2F _cameraScale = { 1, 1 };
	D2D1_POINT_2F _cameraSize = { 1600, 1200 };
	D2D1::Matrix3x2F _cameraTransform;

	void UpdateCameraTransform();
	const D2D1::Matrix3x2F GetCameraTransform() const { return _cameraTransform; }
};

