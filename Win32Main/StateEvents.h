#pragma once
#include "ECSElements.h"

struct StateChange : public Event<StateChange> {
	std::string _prevStateName;
	std::string _curStateName;
	StateChange(std::string prevState, std::string curState) : _prevStateName(prevState), _curStateName(curState) {}
};