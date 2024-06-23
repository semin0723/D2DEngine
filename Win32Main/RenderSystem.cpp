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
	for (auto entity : _renderObject) {
		Transform* transform = entity._obj->GetComponent<Transform>();
		Sprite* sprite = entity._obj->GetComponent<Sprite>();
		D2D1_MATRIX_3X2_F tf = D2D1::Matrix3x2F::Translation(transform->_position.x, transform->_position.y);
		_target->SetTransform(tf);
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