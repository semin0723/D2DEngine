#include "Button.h"
#include "State.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::ChangeState(Button_State state)
{
	_states[_curState]->StateExit();
	_curState = state;
	_states[_curState]->StateEnter();
}

void Button::AddState(Button_State state, State* stateAction)
{
	_states[state] = stateAction;
}
