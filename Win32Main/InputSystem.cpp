#include "InputSystem.h"
#include "windows.h"
#include "Events.h"

InputSystem::InputSystem()
{
	_prevKeyState = new bool[256];
}

InputSystem::~InputSystem()
{
	delete[] _prevKeyState;
}

void InputSystem::PreUpdate(float dt)
{
	for (int i = 0; i < 256; i++) {
		if (GetAsyncKeyState(i) & 0x8000) {
			ECS::_ecs->SendEvent<KeyDown>(i);
		}
		else if (GetAsyncKeyState(i) & 0x8001) {
			ECS::_ecs->SendEvent<Key>(i);
		}
		else if(GetAsyncKeyState(i) & 0x0001){
			ECS::_ecs->SendEvent<KeyUp>(i);
		}
	}
}

void InputSystem::Update(float dt)
{
}

void InputSystem::PostUpdate(float dt)
{
}
