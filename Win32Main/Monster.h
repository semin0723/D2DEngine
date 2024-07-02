#pragma once
#include "Entity.h"

class Monster : public Entity<Monster>
{
public:
	void Initialize();
};

