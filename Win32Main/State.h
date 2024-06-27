#pragma once
#include "globalheader.h"

class State {
public:
	State() {}
	virtual ~State() {}

private:
	std::string _stateName;
};