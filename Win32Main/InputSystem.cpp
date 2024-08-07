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
	UpdateMouse(dt);
	
	HWND hWnd = GetFocus();
	if (hWnd == nullptr) return;

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

void InputSystem::UpdateMouse(float dt)
{
	static float accumulateTime;
	_prevMouseState = _curMouseState;

	POINT pos;
	GetCursorPos(&pos);
	HWND curWindow = GetFocus();

	ScreenToClient(curWindow, &pos);

	_curMouseState._position.x = (FLOAT)pos.x;
	_curMouseState._position.y = (FLOAT)pos.y;

	accumulateTime += dt;
	if (accumulateTime >= _throttleInverval) {
		accumulateTime -= _throttleInverval;
		ecs->SendEvent<MouseMove>(_curMouseState._position);
	}

	_curMouseState._mouseLButton = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	_curMouseState._mouseRButton = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

	// MouseButtonDown
	if (_prevMouseState._mouseLButton == false && _curMouseState._mouseLButton == true) {
		ecs->SendEvent<MouseButtonDown>(VK_LBUTTON, _curMouseState._position, dt);
	}
	else if (_prevMouseState._mouseRButton == false && _curMouseState._mouseRButton == true) {
		ecs->SendEvent<MouseButtonDown>(VK_RBUTTON, _curMouseState._position, dt);
	}

	// MouseButton
	if (_prevMouseState._mouseLButton == true && _curMouseState._mouseLButton == true) {
		ecs->SendEvent<MouseButton>(VK_LBUTTON, _curMouseState._position, dt);
	}
	else if (_prevMouseState._mouseRButton == true && _curMouseState._mouseRButton == true) {
		ecs->SendEvent<MouseButton>(VK_RBUTTON, _curMouseState._position, dt);
	}

	// MouseButtonUp
	if (_prevMouseState._mouseLButton == true && _curMouseState._mouseLButton == false) {
		ecs->SendEvent<MouseButtonUp>(VK_LBUTTON, _curMouseState._position, dt);
	}
	else if (_prevMouseState._mouseRButton == true && _curMouseState._mouseRButton == false) {
		ecs->SendEvent<MouseButtonUp>(VK_RBUTTON, _curMouseState._position, dt);
	}
}
