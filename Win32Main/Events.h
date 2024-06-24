#pragma once
#include "ECSElements.h"

struct KeyDown : public Event<KeyDown> {
	const int _keyCode;
	const float _delta;
	KeyDown(const int keyCode, const float delta) : _keyCode(keyCode), _delta(delta) {}
};
struct KeyUp : public Event<KeyUp> {
	const int _keyCode;
	const float _delta;
	KeyUp(const int keyCode, const float delta) : _keyCode(keyCode), _delta(delta) {}
};
struct Key : public Event<Key> {
	const int _keyCode;
	const float _delta;
	Key(const int keyCode, const float delta) : _keyCode(keyCode), _delta(delta) {}
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