#include "ColliderSystem.h"

ColliderSystem::ColliderSystem()
{
	RegistEvent();
}

ColliderSystem::~ColliderSystem()
{
	UnRegistEvent();
}

void ColliderSystem::PostUpdate(float dt)
{

}

void ColliderSystem::SetCollisionMatrix(Object_Layer layer1, Object_Layer layer2)
{

}

void ColliderSystem::RegistEvent()
{
	RegisterCallback(&ColliderSystem::OnGameObjectCreated);
}

void ColliderSystem::UnRegistEvent()
{
	UnRegisterCallback(&ColliderSystem::OnGameObjectCreated);
}

void ColliderSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
	_registeredEntity[(UINT)event->_layer].push_back(event->_entityId);
}
