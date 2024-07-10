#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class State;

class ButtonComponent : public Component<ButtonComponent>
{
public:
	ButtonComponent();
	~ButtonComponent();

	void SetOwner(EntityId id);
	void ChangeState(Button_State state);
	void AddState(Button_State state, State* stateAction);

	Button_State _curState = Button_State::Normal;
	std::map<Button_State, State*> _states;
};

