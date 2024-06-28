#pragma once
#include "ECSElements.h"
#include "globalheader.h"
#include "ECSCall.h"
#include "State.h"

class StateComponent : public Component<StateComponent>
{
public:
	StateComponent();
	~StateComponent();

	void AddState(std::string& stateName, State* state);
	void RemoveState(std::string& stateName);
	void ChangeState(std::string& prevStateName, std::string& curStateName);

private:
	std::unordered_map<std::string, State*> _states;
	std::string _curStateName;
};

