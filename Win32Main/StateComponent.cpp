#include "StateComponent.h"
#include "StateEvents.h"

StateComponent::StateComponent()
{
}

StateComponent::~StateComponent()
{
	for (auto& i : _states) {
		delete i.second;
	}
}

void StateComponent::AddState(std::string& stateName, State* state)
{
	_states[stateName] = state;
}

void StateComponent::RemoveState(std::string& stateName)
{
	delete _states[stateName];
	_states[stateName] = nullptr;
}

void StateComponent::ChangeState(std::string& prevStateName, std::string& curStateName)
{
	if (_states[curStateName] != nullptr) {
		ECS::_ecs->SendEvent<StateChange>(prevStateName, curStateName);
	}
}
