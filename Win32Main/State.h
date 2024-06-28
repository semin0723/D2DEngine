#pragma once
#include "globalheader.h"

class State {
public:
	State() {}
	virtual ~State() {}

	virtual void StateEnter() = 0;
	virtual void StateUpdate(float dt) = 0;
	virtual void StateExit() = 0;

private:
	std::string _stateName;
};