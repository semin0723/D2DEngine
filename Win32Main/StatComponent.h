#pragma once
#include "ECSElements.h"

class StatComponent : Component<StatComponent>
{
public:
	StatComponent() {}
	~StatComponent() {}

	int _hp = 0;
	int _damage = 0;
	int _defence = 0;
	float _moveSpeed = 0;
};

