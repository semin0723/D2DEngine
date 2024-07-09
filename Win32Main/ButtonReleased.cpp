#include "ButtonReleased.h"
#include "Components.h"

ButtonReleased::ButtonReleased()
{
}

ButtonReleased::~ButtonReleased()
{
}

void ButtonReleased::StateEnter()
{
}

void ButtonReleased::StateUpdate(float dt)
{
	static float accumulateTime;
	accumulateTime += dt;
	if (accumulateTime >= _stateChangeInterval) {
		accumulateTime = 0;
		Button* btn = ComponentManager->Getcomponent<Button>(_owner);
		btn->ChangeState(Button_State::Normal);
	}
}

void ButtonReleased::StateExit()
{
}
