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
			ecs->SendEvent<KeyDown>(i, dt);
		}
	}
}

void InputSystem::Update(float dt)
{
}

void InputSystem::PostUpdate(float dt)
{
}
