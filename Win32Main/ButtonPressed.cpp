#include "ButtonPressed.h"
#include "Components.h"

ButtonPressed::ButtonPressed()
{
}

ButtonPressed::~ButtonPressed()
{
}

void ButtonPressed::StateEnter()
{
	Sprite* sp = ComponentManager->Getcomponent<Sprite>(_owner);
	sp->GetImage(L"ButtonPressed");
}

void ButtonPressed::StateUpdate(float dt)
{
}

void ButtonPressed::StateExit()
{
}
