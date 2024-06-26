#include "RenderSystem.h"
#include "Sprite.h"
#include "Transform.h"
#include "BoxCollider.h"

RenderSystem::RenderSystem(ID2D1HwndRenderTarget* target) : _target(target)
{
	_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &_greenBrush);
	RegistEvent();
}

RenderSystem::~RenderSystem()
{
	_greenBrush->Release();
	UnRegistEvent();
}

void RenderSystem::Update(float dt)
{
	for (int i = 0; i < (UINT)Object_Layer::End; i++) {
		for (auto& entity : _renderObject[i]) {
			Transform* transform = entity._obj->GetComponent<Transform>();
			Sprite* sprite = entity._obj->GetComponent<Sprite>();
			//Vector3 spriteMidPos(sprite->_spriteSize.x / 2.0f, sprite->_spriteSize.y / 2.0f, 0);
			//_target->SetTransform(CalcTransform(transform->_position, transform->_scale, transform->_rotate, spriteMidPos));
			_target->SetTransform(transform->GetTransform());
			_target->DrawBitmap(sprite->_sprite->_bitmap);

			BoxCollider* bc = entity._obj->GetComponent<BoxCollider>();
			if (bc == nullptr) continue;
			_target->DrawRectangle(
				D2D1::RectF(
					bc->_borderPos[0].x, bc->_borderPos[0].y,
					bc->_borderPos[2].x, bc->_borderPos[2].y
				),
				_greenBrush
			);
		}
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
	_renderObject[(UINT)event->_layer].push_back(RenderObject(event->_entityId, entity));
}

D2D1_MATRIX_3X2_F RenderSystem::CalcTransform(Vector3& pos, Vector3& scale, Vector3& rot, Vector3& spriteMid)
{
	return D2D1::Matrix3x2F::Scale(D2D1::SizeF(scale.x, scale.y)) *
		D2D1::Matrix3x2F::Rotation(rot.z, D2D1::Point2F(spriteMid.x, spriteMid.y)) *
		D2D1::Matrix3x2F::Translation(pos.x, pos.y)
		;
}
