#pragma once
#include "ECSCall.h"
#include "EventListener.h"
#include "ECSElements.h"
#include "Events.h"

class PlayerControllSystem : public System<PlayerControllSystem>, public EventListener
{
public:
	PlayerControllSystem();
	~PlayerControllSystem();

	void RegistEvent();
	void UnRegistEvent();

	void OnPlayerCreated(const RegistPlayer* event);
	void OnKeyDown(const KeyDown* event);
	void OnKey(const Key* event);
	void OnKeyUp(const KeyUp* event);

private:
	EntityId _playerId;

};

