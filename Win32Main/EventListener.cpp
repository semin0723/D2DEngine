#include "EventListener.h"
#include "ECSCall.h"

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	UnRegisterAllCallbacks();
}

void EventListener::UnRegisterAllCallbacks()
{
	for (auto delegate : _callbacks) {
		ECS::_ecs->UnSubscribeEvent(delegate);
	}
	_callbacks.clear();
}
