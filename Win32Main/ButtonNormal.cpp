#include "ButtonNormal.h"
#include "Components.h"

ButtonNormal::ButtonNormal()
{
}

ButtonNormal::~ButtonNormal()
{
}

void ButtonNormal::StateEnter()
{
	Sprite* sp = ComponentManager->Getcomponent<Sprite>(_owner);
	sp->GetImage(L"ButtonNormal");
}

void ButtonNormal::StateUpdate(float dt)
{
}

void ButtonNormal::StateExit()
{
}
