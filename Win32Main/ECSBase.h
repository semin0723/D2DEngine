#pragma once
#include "EventHandler.h"
#include "EventDelegate.h"

class EventListener;
class IEvent;
class EventHandler;

class EntityManager;
class SystemManager;
class ComponentManager;

class ECSBase
{
public:
	ECSBase();
	~ECSBase();

/*
	GetManagers()
*/
	template<class E, class ...ARGS>
	void SendEvent(ARGS&&... eventArgs) {
		_eventHandler->Send<E>(std::forward<ARGS>(eventArgs)...);
	}

	void Update(float dt);

	EntityManager* GetEntityManager() { return _entityManager; }
	SystemManager* GetSystemManager() { return _systemManager; }
	ComponentManager* GetComponentManager() { return _componentManager; }

private:
	EventHandler* _eventHandler;
	EntityManager* _entityManager;
	SystemManager* _systemManager;
	ComponentManager* _componentManager;

	ECSBase(const ECSBase&) = delete;
	ECSBase& operator=(ECSBase&) = delete;

	template<class E>
	void SubscribeEvent(IEventDelegate* const eventDelegate) {
		_eventHandler->AddEventCallback<E>(eventDelegate);
	}

	void UnSubscribeEvent(IEventDelegate* eventDelegate) {
		_eventHandler->RemoveEventCallback(eventDelegate);
	}

	friend class IEvent;
	friend class EventListener;
	friend class EntityManager;
};

