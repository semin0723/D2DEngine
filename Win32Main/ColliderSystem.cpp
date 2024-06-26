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

			bool isCollision = IsPointInSquare(bcLeft->_calculatedBorderPos, bcRight->_calculatedBorderPos);
			std::pair<UINT, UINT> collisionKey = { (std::min)(i._index, j._index), (std::max)(i._index, j._index) };

			if (bcLeft->_isTrigger == true || bcRight->_isTrigger == true) {
				if (_collisionHistory[collisionKey] == false) {
					if (isCollision == true) {
						//ECS::_ecs->SendEvent<TriggerEnter>(i, j);
						_collisionHistory[collisionKey] = true;
					}
				}
				else {
					if (isCollision == true) {
						//ECS::_ecs->SendEvent<TriggerStay>(i, j);
					}
					else {
						//ECS::_ecs->SendEvent<TriggerExit>(i, j);
						_collisionHistory[collisionKey] = false;
					}
				}
			}
			else {
				if (_collisionHistory[collisionKey] == false) {
					if (isCollision == true) {
						//ECS::_ecs->SendEvent<CollisionEnter>(i, j);
						_collisionHistory[collisionKey] = true;
					}
				}
				else {
					if (isCollision == true) {
						//ECS::_ecs->SendEvent<CollisionStay>(i, j);
					}
					else {
						//ECS::_ecs->SendEvent<CollisionExit>(i, j);
						_collisionHistory[collisionKey] = false;
					}
				}
			}
		}
	}
}

bool ColliderSystem::IsPointInSquare(std::vector<D2D1_POINT_2F>& left, std::vector<D2D1_POINT_2F>& right)
{
	for (int i = 0; i < left.size(); i++) {
		bool isPointInShape = true;
		for (int j = 0; j < right.size(); j++) {
			int pointIdx = (j + 1) % right.size();
			if (CCW(right[j], left[i], right[pointIdx]) < 0) {
				isPointInShape = false;
				break;
			}
		}
		if (isPointInShape == false) {
			return false;
		}
	}
	return true;
}

float ColliderSystem::CCW(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_POINT_2F p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
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
