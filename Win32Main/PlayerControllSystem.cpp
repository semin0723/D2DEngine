 #include "PlayerControllSystem.h"
#include "Transform.h"
#include "BoxCollider.h"

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
	Transform* tf = ComponentManager->Getcomponent<Transform>(_playerId);
	BoxCollider* bc = ComponentManager->Getcomponent<BoxCollider>(_playerId);
	Vector3 moveVector;
	if (event->_keyCode == 0x25) {
		moveVector += Vector3(-200, 0, 0) * event->_delta;
		tf->_position += moveVector;
		tf->CalcRotation(moveVector);
		bc->SetBorderLocation(tf->GetTransform());
	}
	if (event->_keyCode == 0x26) {
		moveVector += Vector3(0, -200, 0) * event->_delta;
		tf->_position += moveVector;
		tf->CalcRotation(moveVector);
		bc->SetBorderLocation(tf->GetTransform());
	}
	if (event->_keyCode == 0x27) {
		moveVector += Vector3(200, 0, 0) * event->_delta;
		tf->_position += moveVector;
		tf->CalcRotation(moveVector);
		bc->SetBorderLocation(tf->GetTransform());
	}
	if (event->_keyCode == 0x28) {
		moveVector += Vector3(0, 200, 0) * event->_delta;
		tf->_position += moveVector;
		tf->CalcRotation(moveVector);
		bc->SetBorderLocation(tf->GetTransform());
	}
}

void PlayerControllSystem::OnKeyUp(const KeyUp* event)
{
}
