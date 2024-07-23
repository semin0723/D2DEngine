#pragma once
#include "ECSElements.h"
#include "globalheader.h"

struct RoundEnd : public Event<RoundEnd> {

	RoundEnd() {}
};

struct RoundStart : public Event<RoundStart> {

	RoundStart() {}
};

struct GameOver : public Event<GameOver> {

	GameOver() {}
};

struct GameWin : public Event<GameWin> {

	GameWin() {}
};

struct GamePause : public Event<GamePause> {

	GamePause() {}
};

struct Attack : public Event<Attack> {
	EntityId _target;
	int _damage;
	Attack(EntityId eid, int damage) : _target(eid), _damage(damage) {}
};

struct AreaAttack : public Event<AreaAttack> {
	EntityId _target;
	int _damage;
	Vector3 _rectSize;
	AreaAttack(EntityId eid, int damage, Vector3 size) : _target(eid), _damage(damage), _rectSize(size) {}
};

struct CreateEffect : public Event<CreateEffect> {
	std::wstring _effectKey;
	Vector3 _createLocation;
	CreateEffect(std::wstring key, Vector3 location) : _effectKey(key), _createLocation(location) {}
};

struct GetMoney : public Event<GetMoney> {
	Money_Type _moneyType;
	UINT _earn;
	GetMoney(Money_Type type, UINT cost) : _moneyType(type), _earn(cost) {}
};

struct DecreseLife : public Event<DecreseLife> {
	UINT _life;
	DecreseLife(UINT life) : _life(life) {}
};

struct UIStateChange : public Event< UIStateChange> {
	EntityId _eid;
	bool _state;
	UIStateChange(EntityId id, bool state) : _eid(id), _state(state) {}
};

struct GameInitialize : public Event<GameInitialize> {

	GameInitialize() {}
};