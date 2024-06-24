#include "RenderSystem.h"
#include "BoxComponent.h"
#include "Sprite.h"
#include "Transform.h"

RenderSystem::RenderSystem(ID2D1HwndRenderTarget* target) : _target(target)
{
	_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &_blackBrush);
	RegistEvent();
}

RenderSystem::~RenderSystem()
{
	_blackBrush->Release();
	UnRegistEvent();
}

void RenderSystem::Update(float dt)
{
	for (auto& entity : _renderObject) {
		Transform* transform = entity._obj->GetComponent<Transform>();
		Sprite* sprite = entity._obj->GetComponent<Sprite>();
		Vector3 midPos(transform->_position.x - sprite->_sprite->_bitmap->GetSize().width / 2.0f, transform->_position.y - sprite->_sprite->_bitmap->GetSize().height / 2.0f, 0);
		_target->SetTransform(CalcTransform(transform->_position, transform->_scale, transform->_rotate, midPos));
		_target->DrawBitmap(sprite->_sprite->_bitmap);
	}
}

void RenderSystem::RegistEvent()
{
	RegisterCallback(&RenderSystem::eventTest);
}

void RenderSystem::UnRegistEvent()
{
	UnRegisterCallback(&RenderSystem::eventTest);
}

void RenderSystem::eventTest(const GameObjectCreated* event)
{
	IEntity* entity = ECS::_ecs->GetEntityManager()->GetEntity(event->_entityId);
	_renderObject.push_back(RenderObject(event->_entityId, entity));
}

D2D1_MATRIX_3X2_F RenderSystem::CalcTransform(Vector3& pos, Vector3& scale, Vector3& rot, Vector3& drawOffset)
{
	return D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y)) *
		D2D1::Matrix3x2F::Translation(drawOffset.x, drawOffset.y) *
		D2D1::Matrix3x2F::Rotation(rot.z, D2D1::Point2F(pos.x, pos.y))
		;
}
