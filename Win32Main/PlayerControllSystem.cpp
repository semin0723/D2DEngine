#include "PlayerControllSystem.h"
#include "Transform.h"

PlayerControllSystem::PlayerControllSystem()
{
	RegistEvent();
}

PlayerControllSystem::~PlayerControllSystem()
{
	UnRegistEvent();
}

void PlayerControllSystem::RegistEvent()
{
	RegisterCallback(&PlayerControllSystem::OnPlayerCreated);
	RegisterCallback(&PlayerControllSystem::OnKeyDown);
	RegisterCallback(&PlayerControllSystem::OnKey);
	RegisterCallback(&PlayerControllSystem::OnKeyUp);
}

void PlayerControllSystem::UnRegistEvent()
{
	UnRegisterCallback(&PlayerControllSystem::OnPlayerCreated);
	UnRegisterCallback(&PlayerControllSystem::OnKeyDown);
	UnRegisterCallback(&PlayerControllSystem::OnKey);
	UnRegisterCallback(&PlayerControllSystem::OnKeyUp);
}

void PlayerControllSystem::OnPlayerCreated(const RegistPlayer* event)
{
	_playerId = event->_entityId;
}

void PlayerControllSystem::OnKeyDown(const KeyDown* event)
{

}

void PlayerControllSystem::OnKey(const Key* event)
{
	Transform* tf = ECS::_ecs->GetComponentManager()->Getcomponent<Transform>(_playerId);
	if (event->_keyCode == 0x25) {
		tf->_position += Vector3(-1, 0, 0);
	}
	if (event->_keyCode == 0x26) {
		tf->_position += Vector3(0, -1, 0);
	}
	if (event->_keyCode == 0x27) {
		tf->_position += Vector3(1, 0, 0);
	}
	if (event->_keyCode == 0x28) {
		tf->_position += Vector3(1, 0, 0);
	}
}

void PlayerControllSystem::OnKeyUp(const KeyUp* event)
{
}
