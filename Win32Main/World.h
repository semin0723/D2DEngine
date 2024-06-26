#pragma once
#include "ECSElements.h"
#include "EventListener.h"
#include "globalheader.h"
#include "Events.h"

class World : public System<World>, public EventListener
{
public:
	World();
	~World();

	virtual void PreUpdate(float dt);
	virtual void Update(float dt);
	virtual void PostUpdate(float dt);

private:
	std::vector<EntityId> _objects;

	void RegistEvent();
	void UnRegistEvent();

	template<class E>
	EntityId CreateGameObject(Object_Layer layer) {
		EntityId eid = ECS::_ecs->GetEntityManager()->CreateEntity<E>();
		ECS::_ecs->SendEvent<GameObjectCreated>(eid, layer);
		return eid;
	}

	EntityId _monsterId; // 테스트용
};

