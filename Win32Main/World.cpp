#include "World.h"
#include "ECSCall.h"
#include "Square.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Sprite.h"

World::World()
{
	_mainCamera = new Camera;

	EntityId square = CreateGameObject<Square>(Object_Layer::Player);
	Transform* tf = ECS::_ecs->GetComponentManager()->AddComponent<Transform>(square, Vector3(100.0f, 100.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite* sp = ECS::_ecs->GetComponentManager()->AddComponent<Sprite>(square, L"TowerTest");
	tf->SetRectSize(sp->_spriteSize);
	BoxCollider* bc = ECS::_ecs->GetComponentManager()->AddComponent<BoxCollider>(square, sp->_spriteSize);
	ECS::_ecs->SendEvent<RegistPlayer>(square);

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
