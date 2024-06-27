#include "StateComponent.h"
#include "ECSCall.h"

StateComponent::StateComponent()
{
}

StateComponent::~StateComponent()
{
}

void StateComponent::AddState(std::string& stateName, State& state)
{
	_states[stateName] = state;
}

void StateComponent::RemoveState(std::string& stateName)
{
	_states[stateName].~State();
}

void StateComponent::ChangeState(std::string& prevStateName, std::string& curStateName)
{
	//ECS::_ecs->SendEvent<StateChange>(prevStateName, curStateName);
}
