#include "UITransform.h"
#include "ECSCall.h"

UITransform::UITransform() : _position{ 0, 0, 0 }, _scale{ 1.0f, 1.0f, 1.0f }, _rotate{ 0, 0, 0 }
{
	UpdateTransform();
}

UITransform::UITransform(Vector3 pos, Vector3 scale, Vector3 rotate) : _position(pos), _scale(scale), _rotate(rotate)
{
	UpdateTransform();
}

void UITransform::UpdateTransform()
{
	_relativeTransform =
		D2D1::Matrix3x2F::Scale(_scale.x, _scale.y) *
		D2D1::Matrix3x2F::Rotation(_rotate.z) *
		D2D1::Matrix3x2F::Translation(_position.x, _position.y)
		;
}

void UITransform::UpdatePosition()
{
	UpdateTransform();

	EntityId parent = EntityManager->GetEntity(_owner)->GetParentEntityId();

	// no parent
	if (parent._index == (std::numeric_limits<ULL>::max)() && parent._version == (std::numeric_limits<ULL>::max)()) {
		_screenTransform = _relativeTransform;
	}
	else {
		UITransform* parentUItf = ComponentManager->Getcomponent<UITransform>(parent);
		_screenTransform = parentUItf->_screenTransform * _relativeTransform;
	}
}

const Vector3 UITransform::GetScreenPosition() const
{
	D2D1_POINT_2F pos = { 0, 0 };
	pos = pos * _screenTransform;
	return Vector3(pos.x, pos.y, 0);
}
