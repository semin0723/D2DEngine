#include "Camera.h"

void Camera::UpdateCameraTransform()
{
	_cameraTransform = 
		D2D1::Matrix3x2F::Scale(_cameraScale.x, _cameraScale.y) *
		D2D1::Matrix3x2F::Rotation(0) *
		D2D1::Matrix3x2F::Translation(_cameraPosition.x, _cameraPosition.y)
		;
}
