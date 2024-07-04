#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class AttackComponent : public Component<AttackComponent>
{
public:
	AttackComponent() {}
	AttackComponent(int damage) : _damage(damage) {}
	AttackComponent(int damage, bool multi, Vector3 rect) : _damage(damage), _multiAttack(multi), _attackRect(rect) {}
	~AttackComponent() {}

	int _damage = 0;
	bool _multiAttack = false;
	Vector3 _attackRect;
};

