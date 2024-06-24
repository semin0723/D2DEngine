#pragma once
#include "ECSElements.h"

struct KeyDown : public Event<KeyDown> {
	const int _keyCode;
	KeyDown(const int keyCode) : _keyCode(keyCode) {}
};
struct KeyUp : public Event<KeyUp> {
	const int _keyCode;
	KeyUp(const int keyCode) : _keyCode(keyCode) {}
};
struct Key : public Event<Key> {
	const int _keyCode;
	Key(const int keyCode) : _keyCode(keyCode) {}
};

struct GameObjectCreated : public Event<GameObjectCreated> {
	EntityId _entityId;
	GameObjectCreated(EntityId eid) : _entityId(eid) {}
};

struct CreateSprite : public Event<CreateSprite> {
	EntityId _entityId;
	std::wstring _spriteKey;
	CreateSprite(EntityId eid, std::wstring spkey) : _entityId(eid), _spriteKey(spkey) {}
};

struct RegistPlayer : public Event<RegistPlayer> {
	EntityId _entityId;
	RegistPlayer(EntityId eid) : _entityId(eid) {}
};