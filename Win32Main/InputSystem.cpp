#include "InputSystem.h"
#include "windows.h"
#include "Events.h"

InputSystem::InputSystem() : _keyState(256, false)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::PreUpdate(float dt)
{
	for (int i = 0; i < 256; i++) {
		if (GetAsyncKeyState(i) & 0x8000) {
			if (_keyState[i] == false) {
				_keyState[i] = true;
				ecs->SendEvent<KeyDown>(i, dt);
			}
			else {
				ecs->SendEvent<Key>(i, dt);
			}
		}
		else {
			if (_keyState[i] == true) {
				_keyState[i] = false;
				ecs->SendEvent<KeyUp>(i, dt);
			}
		}
	}
}

void InputSystem::Update(float dt)
{
}

void InputSystem::PostUpdate(float dt)
{
}
