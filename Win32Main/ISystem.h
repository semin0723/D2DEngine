#pragma once
#include "utilheader.h"

class System;

using SystemTypeId = TypeId;
static const SystemTypeId INVALID_SYSTEM = INVALID_TYPE_ID;

class ISystem
{
public:
	virtual ~ISystem() {}

	virtual const SystemTypeId GetTypeId() const = 0;
	virtual const std::string& GetSystemTypeName() const = 0;

	virtual void PreUpdate(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void PostUpdate(float dt) = 0;

protected:
	ISystem(float updateInterval = -1.0f) : _lastUpdateTime(0), _updateInterval(updateInterval) {}

private:
	float _lastUpdateTime;
	float _updateInterval;

	bool _enabled	: true;	
	bool _canUpdate	: true;

	friend class SystemManager;
};

