#pragma once
#include "globalheader.h"
#include "ECSElements.h"

class State {
public:
	State() {}
	virtual ~State() {}

	virtual void StateEnter() = 0;
	virtual void StateUpdate(float dt) = 0;
	virtual void StateExit() = 0;

	void SetOwner(EntityId id) { _owner = id; }
protected:
	EntityId _owner;

private:
	std::string _stateName;
};