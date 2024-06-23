#pragma once
#include "ECSElements.h"

struct GameObjectCreated : public Event<GameObjectCreated> {
	EntityId _entityId;
	GameObjectCreated(EntityId eid) : _entityId(eid) {}
};

struct CreateSprite : public Event<CreateSprite> {
	EntityId _entityId;
	std::wstring _spriteKey;
	CreateSprite(EntityId eid, std::wstring spkey) : _entityId(eid), _spriteKey(spkey) {}
};