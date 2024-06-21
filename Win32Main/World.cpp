#include "World.h"
#include "ECSCall.h"
#include "Square.h"
#include "Transform.h"

World::World()
{
	EntityId square = CreateGameObject<Square>();
	ECS::_ecs->GetComponentManager()->AddComponent<Transform>(square, Vector3(100.0f, 100.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
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
