#pragma once
#include "ECSCall.h"
#include "ECSElements.h"
#include "EventListener.h"
#include "globalheader.h"

class InputSystem : public System<InputSystem>, public EventListener
{
public:
	InputSystem();
	~InputSystem();

	virtual void PreUpdate(float dt);
	virtual void Update(float dt);
	virtual void PostUpdate(float dt);

	class Mouse {
	public:
		D2D1_POINT_2F _position = { 0, 0 };

		bool _mouseLButton = false;
		bool _mouseRButton = false;
	};

	void UpdateMouse(float dt);


private:
	std::vector<bool> _keyState;
	Mouse _curMouseState;
	Mouse _prevMouseState;
	float _throttleInverval = 0.01667f;
};

