#pragma once
#include "ECSElements.h"

struct GameObjectCreated : public Event<GameObjectCreated> {
	EntityId _entityId;
	EntityTypeId _entityTypeId;
	GameObjectCreated(EntityId eid, EntityTypeId etid) : _entityId(eid), _entityTypeId(etid) {}
};