#pragma once
#include "ECSElements.h"

class StatComponent : public Component<StatComponent>
{
public:
	StatComponent() {}
	~StatComponent() {}

	int _damage = 0;
	float _criticalRate = 0;
	bool _multiAttack = false;
};

