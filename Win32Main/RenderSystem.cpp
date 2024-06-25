#include "RenderSystem.h"
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
		Vector3 spriteMidPos(sprite->_spriteSize.x / 2.0f, sprite->_spriteSize.y / 2.0f, 0);
		_target->SetTransform(CalcTransform(transform->_position, transform->_scale, transform->_rotate, spriteMidPos));
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

D2D1_MATRIX_3X2_F RenderSystem::CalcTransform(Vector3& pos, Vector3& scale, Vector3& rot, Vector3& spriteMid)
{
	return D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y)) *
		D2D1::Matrix3x2F::Rotation(rot.z, D2D1::Point2F(spriteMid.x, spriteMid.y)) *
		D2D1::Matrix3x2F::Translation(pos.x, pos.y)
		;
}
