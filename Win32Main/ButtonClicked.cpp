#include "ButtonClicked.h"
#include "Components.h"

ButtonClicked::ButtonClicked()
{
}

ButtonClicked::~ButtonClicked()
{
}

void ButtonClicked::StateEnter()
{
	Button* btn = ComponentManager->Getcomponent<Button>(_owner);
	btn->ChangeState(Button_State::Normal);
}

void ButtonClicked::StateUpdate(float dt)
{
}

void ButtonClicked::StateExit()
{
}
