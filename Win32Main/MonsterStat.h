#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class MonsterStat : public Component<MonsterStat>
{
public:
	MonsterStat() {}
	~MonsterStat() {}

	int _hp = 0;
	int _defence = 0;
	float _moveSpeed = 0;

};

