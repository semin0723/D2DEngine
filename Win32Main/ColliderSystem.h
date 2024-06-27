#pragma once
#include "ECSCall.h"
#include "EventListener.h"
#include "ECSElements.h"
#include "globalheader.h"
#include "Events.h"

class ColliderSystem : public System<ColliderSystem>, public EventListener
{
public:
	ColliderSystem();
	~ColliderSystem();

	virtual void PostUpdate(float dt);

	void SetCollisionMatrix(Object_Layer layer1, Object_Layer layer2);
	void RegistEvent();
	void UnRegistEvent();

	void CheckCollision(UINT layer1Idx, UINT layer2Idx);
	bool ChackOverLap(std::vector<D2D1_POINT_2F>& left, std::vector<D2D1_POINT_2F>& right);
	std::pair<float, float> GetMinMax(D2D1_POINT_2F axis, std::vector<D2D1_POINT_2F>& points);
	bool CheckPointLoc(std::pair<float, float>& left, std::pair<float, float>& right);

	void OnGameObjectCreated(const GameObjectCreated* event);

private:
	UINT _collisionMatrix[(UINT)Object_Layer::End] = {};
	std::map<std::pair<UINT, UINT>, bool> _collisionHistory;
	std::vector<EntityId> _registeredEntity[(UINT)Object_Layer::End] = {};
};

