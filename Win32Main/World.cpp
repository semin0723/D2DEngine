#include "World.h"
#include "ECSCall.h"
#include "Square.h"
#include "Transform.h"
#include "BoxComponent.h"

World::World()
{
	EntityId square = CreateGameObject<Square>();
	ECS::_ecs->GetComponentManager()->AddComponent<Transform>(square, Vector3(100.0f, 100.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	ECS::_ecs->GetComponentManager()->AddComponent<BoxComponent>(square, 200.0f, 200.0f);
	ECS::_ecs->SendEvent<CreateSprite>(square, L"TestImage");

	EntityId square2 = CreateGameObject<Square>();
	ECS::_ecs->GetComponentManager()->AddComponent<Transform>(square2, Vector3(300.0f, 300.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	ECS::_ecs->GetComponentManager()->AddComponent<BoxComponent>(square2, 200.0f, 200.0f);
	ECS::_ecs->SendEvent<CreateSprite>(square2, L"TestImage");
}

World::~World()
{
	for (int i = 0; i < _objects.size(); i++) {
		ECS::_ecs->GetEntityManager()->DestroyEntity(_objects[i]);
	}
}

void World::PreUpdate(float dt)
{
}

void World::Update(float dt)
{
}

void World::PostUpdate(float dt)
{
}

void World::RegistEvent()
{
}

void World::UnRegistEvent()
{
}
