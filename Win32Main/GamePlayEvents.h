#pragma once
#include "ECSElements.h"
#include "globalheader.h"

struct RoundEnd : public Event<RoundEnd> {
	int _curRound;
	RoundEnd(int cur) : _curRound(cur) {}
};

struct RoundStart : public Event<RoundStart> {
	int _curRound;
	RoundStart(int cur) : _curRound(cur) {}
};

struct GameOver : public Event<GameOver> {
	int _curRound;
	GameOver(int cur) : _curRound(cur) {}
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