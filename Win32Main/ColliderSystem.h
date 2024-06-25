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

	void OnGameObjectCreated(const GameObjectCreated* event);

private:
	UINT _collisionMatrix[(UINT)Object_Layer::End] = {};
	std::vector<EntityId> _registeredEntity[(UINT)Object_Layer::End] = {};
};

