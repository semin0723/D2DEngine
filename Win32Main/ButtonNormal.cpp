#include "ButtonNormal.h"
#include "Components.h"

ButtonNormal::ButtonNormal(const std::string& name)
{
	_stateName = name;
}

ButtonNormal::~ButtonNormal()
{
}

void ButtonNormal::StateEnter()
{
	Sprite* sp = ComponentManager->Getcomponent<Sprite>(_owner);
	sp->GetImage(L"Images\\Button\\" + StringToWstring(_stateName));
}

void ButtonNormal::StateUpdate(float dt)
{
}

void ButtonNormal::StateExit()
{
}
