#include "ColliderSystem.h"
#include "BoxCollider.h"

ColliderSystem::ColliderSystem()
{
	memset(_collisionMatrix, 0, sizeof(_collisionMatrix));
	RegistEvent();
}

ColliderSystem::~ColliderSystem()
{
	UnRegistEvent();
}

void ColliderSystem::PostUpdate(float dt)
{
	for (UINT l1 = 0; l1 < (UINT)Object_Layer::End; l1++) {
		for (UINT l2 = 0; l2 < (UINT)Object_Layer::End; l2++) {
			if (_collisionMatrix[l1] & (1 << l2)) {
				checkCollision(l1, l2);
			}
		}
	}
}

void ColliderSystem::SetCollisionMatrix(Object_Layer layer1, Object_Layer layer2)
{
	// set collisionMatrix between layer1 and layer2
	_collisionMatrix[(UINT)(std::min)(layer1, layer2)] ^= (1 << (UINT)(std::max)(layer1, layer2));
/*
	  5 4 3 2 1
	1 X X X X X
	2 X X X X
	3 X X X
	4 X X
	5 X
*/
}

void ColliderSystem::checkCollision(UINT layer1Idx, UINT layer2Idx)
{
	std::vector<EntityId>& left		= _registeredEntity[layer1Idx];
	std::vector<EntityId>& right	= _registeredEntity[layer2Idx];

	for (auto& i : left) {
		BoxCollider* bcLeft = ECS::_ecs->GetComponentManager()->Getcomponent<BoxCollider>(i);
		if (bcLeft == nullptr) continue;
		for (auto& j : right) {
			BoxCollider* bcRight = ECS::_ecs->GetComponentManager()->Getcomponent<BoxCollider>(j);
			if (bcRight == nullptr) continue;
		}
	}
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
