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

private:
	std::vector<bool> _keyState;
};

