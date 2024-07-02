#pragma once
#include "utilheader.h"

template<class T>
class System;

using SystemTypeId = TypeId;
static const SystemTypeId INVALID_SYSTEM = INVALID_TYPE_ID;

class ISystem
{
public:
	virtual ~ISystem() {}

	virtual const SystemTypeId GetTypeId() const = 0;
	virtual const std::string GetSystemTypeName() const = 0;

	virtual void PreUpdate(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void PostUpdate(float dt) = 0;

protected:
	ISystem(unsigned long long priority = 100, float updateInterval = -1.0f) : _lastUpdateTime(0), _updateInterval(updateInterval), _systemPriority(priority) {}

private:
	float _lastUpdateTime;
	float _updateInterval;
	unsigned long long _systemPriority;

	bool _enabled	= true;	
	bool _canUpdate	= true;

	friend class SystemManager;
};

