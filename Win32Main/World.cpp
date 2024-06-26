#include "World.h"
#include "ECSCall.h"
#include "Square.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Sprite.h"

World::World()
{
	EntityId square = CreateGameObject<Square>(Object_Layer::Player);
	Transform* tf = ECS::_ecs->GetComponentManager()->AddComponent<Transform>(square, Vector3(100.0f, 100.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite* sp = ECS::_ecs->GetComponentManager()->AddComponent<Sprite>(square, L"TestImage");
	tf->SetRectSize(sp->_spriteSize);
	BoxCollider* bc = ECS::_ecs->GetComponentManager()->AddComponent<BoxCollider>(square, sp->_spriteSize);
	ECS::_ecs->SendEvent<RegistPlayer>(square);

	EntityId square2 = CreateGameObject<Square>(Object_Layer::Monster);
	Transform* tf2 = ECS::_ecs->GetComponentManager()->AddComponent<Transform>(square2, Vector3(300.0f, 300.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite* sp2 = ECS::_ecs->GetComponentManager()->AddComponent<Sprite>(square2, L"TestImage");
	tf->SetRectSize(sp2->_spriteSize);
	BoxCollider* bc2 = ECS::_ecs->GetComponentManager()->AddComponent<BoxCollider>(square2, sp2->_spriteSize);
	_monsterId = square2;
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
	Transform* tf = ECS::_ecs->GetComponentManager()->Getcomponent<Transform>(_monsterId);
	BoxCollider* bc = ECS::_ecs->GetComponentManager()->Getcomponent<BoxCollider>(_monsterId);
	bc->SetBorderLocation(tf->GetTransform());

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
