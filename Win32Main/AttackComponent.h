#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class AttackComponent : public Component<AttackComponent>
{
public:
	AttackComponent() {}
	AttackComponent(int damage, float interval)
		: _damage(damage), _attackInterval(interval) {}

	AttackComponent(int damage, bool multi, float interval, Vector3 rect)
		: _damage(damage), _multiAttack(multi), _attackInterval(interval), _attackRect(rect) {}

	~AttackComponent() {}

	int _damage = 0;
	float _attackInterval = 0;
	float _curTime = 0;
	bool _multiAttack = false;
	Vector3 _attackRect;
};

