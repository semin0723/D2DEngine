#pragma once
#include "ECSElements.h"
#include "EnumClass.h"

#include "CollisionEvents.h"
#include "StateEvents.h"
#include "GamePlayEvents.h"

// KeyInput
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

// MouseInput
struct MouseMove : public Event<MouseMove> {
	D2D1_POINT_2F _position;
	MouseMove(D2D1_POINT_2F pos) : _position(pos) {}
};

struct MouseButtonDown : public Event<MouseButtonDown> {
	const int _keyCode;
	D2D1_POINT_2F _position;
	const float _delta;
	MouseButtonDown(const int keyCode, D2D1_POINT_2F pos, const float delta) : _keyCode(keyCode), _position(pos), _delta(delta) {}
};
struct MouseButtonUp : public Event<MouseButtonUp> {
	const int _keyCode;
	D2D1_POINT_2F _position;
	const float _delta;
	MouseButtonUp(const int keyCode, D2D1_POINT_2F pos, const float delta) : _keyCode(keyCode), _position(pos), _delta(delta) {}
};
struct MouseButton : public Event<MouseButton> {
	const int _keyCode;
	D2D1_POINT_2F _position;
	const float _delta;
	MouseButton(const int keyCode, D2D1_POINT_2F pos, const float delta) : _keyCode(keyCode), _position(pos), _delta(delta) {}
};

struct ClickInGame : public Event<ClickInGame> {
	D2D1_POINT_2F _position;
	ClickInGame(D2D1_POINT_2F pos) : _position(pos) {}
};

// Create and Destroy Object
struct GameObjectCreated : public Event<GameObjectCreated> {
	EntityId _entityId;
	Object_Layer _layer;
	GameObjectCreated(EntityId eid, Object_Layer layer) : _entityId(eid), _layer(layer) {}
};
struct GameObjectDestroyed : public Event<GameObjectDestroyed> {
	EntityId _entityId;
	Object_Layer _layer;
	GameObjectDestroyed(EntityId eid, Object_Layer layer) : _entityId(eid), _layer(layer) {}
};

// CreateImage   <<< not use >>> 
struct CreateSprite : public Event<CreateSprite> {
	EntityId _entityId;
	std::wstring _spriteKey;
	CreateSprite(EntityId eid, std::wstring spkey) : _entityId(eid), _spriteKey(spkey) {}
};

// regist Player
struct RegistPlayer : public Event<RegistPlayer> {
	EntityId _entityId;
	RegistPlayer(EntityId eid) : _entityId(eid) {}
};

// Button Clicked	
struct ButtonClick : public Event<ButtonClick> {
	EntityId _entityId;
	ButtonClick(EntityId eid) : _entityId(eid) {}
};