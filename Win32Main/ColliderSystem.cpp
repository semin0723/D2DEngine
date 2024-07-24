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
	if (_isGameRunning == false) return;

	for (UINT l1 = 0; l1 < (UINT)Object_Layer::End; l1++) {
		for (UINT l2 = l1; l2 < (UINT)Object_Layer::End; l2++) {
			if (_collisionMatrix[l1] & (1 << l2)) {
				CheckCollision(l1, l2);
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

void ColliderSystem::CheckCollision(UINT layer1Idx, UINT layer2Idx)
{
	std::vector<EntityId>& left		= _registeredEntity[layer1Idx];
	std::vector<EntityId>& right	= _registeredEntity[layer2Idx];

	for (auto& i : left) {
		BoxCollider* bcLeft = ComponentManager->Getcomponent<BoxCollider>(i);
		if (bcLeft == nullptr) continue;
		for (auto& j : right) {
			BoxCollider* bcRight = ComponentManager->Getcomponent<BoxCollider>(j);
			if (bcRight == nullptr) continue;

			bool isCollision = ChackOverLap(bcLeft->_calculatedBorderPos, bcRight->_calculatedBorderPos);
			std::pair<ULL, ULL> collisionKey = { (std::min)(i._index, j._index), (std::max)(i._index, j._index) };

			if (bcLeft->_isTrigger == true || bcRight->_isTrigger == true) {
				if (_collisionHistory[collisionKey] == false) {
					if (isCollision == true) {
						ECS::_ecs->SendEvent<TriggerEnter>(i, j);
						_collisionHistory[collisionKey] = true;
					}
				}
				else {
					if (isCollision == true) {
						ECS::_ecs->SendEvent<TriggerStay>(i, j);
					}
					else {
						ECS::_ecs->SendEvent<TriggerExit>(i, j);
						_collisionHistory[collisionKey] = false;
					}
				}
			}
			else {
				if (_collisionHistory[collisionKey] == false) {
					if (isCollision == true) {
						ECS::_ecs->SendEvent<CollisionEnter>(i, j);
						_collisionHistory[collisionKey] = true;
					}
				}
				else {
					if (isCollision == true) {
						ECS::_ecs->SendEvent<CollisionStay>(i, j);
					}
					else {
						ECS::_ecs->SendEvent<CollisionExit>(i, j);
						_collisionHistory[collisionKey] = false;
					}
				}
			}
		}
	}
}

bool ColliderSystem::ChackOverLap(std::vector<D2D1_POINT_2F>& left, std::vector<D2D1_POINT_2F>& right)
{
	for (int i = 0; i < left.size(); i++) {
		int nextIdx = (i + 1) % left.size();
		D2D1_POINT_2F v = { left[nextIdx].x - left[i].x, left[nextIdx].y - left[i].y };
		std::pair<float, float> leftminmax = GetMinMax(v, left);
		std::pair<float, float> rightminmax = GetMinMax(v, right);
		if (CheckPointLoc(leftminmax, rightminmax) == false) {
			return false;
		}
	}

	for (int i = 0; i < right.size(); i++) {
		int nextIdx = (i + 1) % right.size();
		D2D1_POINT_2F v = { right[nextIdx].x - right[i].x, right[nextIdx].y - right[i].y };
		std::pair<float, float> leftminmax = GetMinMax(v, left);
		std::pair<float, float> rightminmax = GetMinMax(v, right);
		if (CheckPointLoc(leftminmax, rightminmax) == false) {
			return false;
		}
	}
	return true;
}

std::pair<float, float> ColliderSystem::GetMinMax(D2D1_POINT_2F axis, std::vector<D2D1_POINT_2F>& points)
{
	float minValue = FLT_MAX, maxValue = FLT_MIN;
	Vector3 normal(-axis.y, axis.x, 0);
	normal.Normalized();
	for (int i = 0; i < points.size(); i++) {
		Vector3 point(points[i].x, points[i].y, 0);
		float result = dot(point, normal);
		minValue = (std::min)(result, minValue);
		maxValue = (std::max)(result, maxValue);
	}
	return { minValue, maxValue };
}

bool ColliderSystem::CheckPointLoc(std::pair<float, float>& left, std::pair<float, float>& right)
{
	// { min, max }     ||| left.min   right.min  left.max  right.max  |||    right.min   left.min   right.max  left.max |||
	if ((left.first <= right.first && right.first <= left.second) || (left.first <= right.second && right.second <= left.second)) {
		return true;
	}
	return false;
}

void ColliderSystem::RegistEvent()
{
	RegisterCallback(&ColliderSystem::OnGameObjectCreated);
	RegisterCallback(&ColliderSystem::OnGamePause);
	RegisterCallback(&ColliderSystem::OnGameInitialize);
}

void ColliderSystem::UnRegistEvent()
{
	UnRegisterCallback(&ColliderSystem::OnGameObjectCreated);
	UnRegisterCallback(&ColliderSystem::OnGamePause);
	UnRegisterCallback(&ColliderSystem::OnGameInitialize);
}

void ColliderSystem::OnGameInitialize(const GameInitialize* event)
{
	for (UINT i = 0; i < (UINT)Object_Layer::UI; i++) {
		_registeredEntity->clear();
	}
	_collisionHistory.clear();
}

void ColliderSystem::OnGameObjectCreated(const GameObjectCreated* event)
{
	_registeredEntity[(UINT)event->_layer].push_back(event->_entityId);
}

void ColliderSystem::OnGamePause(const GamePause* event)
{
	_isGameRunning ^= true;
}
