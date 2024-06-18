#include "ECSBase.h"

ECSBase::ECSBase()
{
	_eventHandler = new EventHandler;
}

ECSBase::~ECSBase()
{
	delete _eventHandler;
	_eventHandler = nullptr;
}

void ECSBase::Update()
{
	_eventHandler->DispatchEvents();
}
