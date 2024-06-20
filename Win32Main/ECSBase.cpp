#include "ECSBase.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "ComponentManager.h"

ECSBase::ECSBase()
{
	_eventHandler = new EventHandler;
	_systemManager = new SystemManager;
	_componentManager = new ComponentManager;
	_entityManager = new EntityManager(_componentManager);
}

ECSBase::~ECSBase()
{
	delete _entityManager;
	_entityManager = nullptr;

	delete _componentManager;
	_componentManager = nullptr;

	delete _systemManager;
	_systemManager = nullptr;

	delete _eventHandler;
	_eventHandler = nullptr;
}

void ECSBase::Update(float dt)
{
	_systemManager->Update(dt);
	_eventHandler->DispatchEvents();
	_entityManager->RemoveDestroyEntities();
	_eventHandler->DispatchEvents();
}
