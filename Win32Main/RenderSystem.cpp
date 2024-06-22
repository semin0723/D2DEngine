#include "RenderSystem.h"
#include "BoxComponent.h"
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
		BoxComponent* bc = entity._obj->GetComponent<BoxComponent>();
		_target->FillRectangle(D2D1::RectF(transform->_position.x, transform->_position.y, bc->_width, bc->_height), _blackBrush);
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