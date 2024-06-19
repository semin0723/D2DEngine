#pragma once
#include "IEntity.h"

using ComponentId		= ObjectId;
using ComponentTypeId	= TypeId;

static const ComponentId INVALID_COMPONENT_ID = INVALID_OBJECT_ID;

template<class T>
class Component;

class IComponent
{
public:
	IComponent() {}
	virtual ~IComponent() {}

	// 컴포넌트가 같은지의 확인을 해시로 변경된 컴포넌트의 id값으로 한다.
	const bool operator==(const IComponent& other) const { return _hashValue == other._hashValue; }
	const bool operator!=(const IComponent& other) const { return _hashValue != other._hashValue; }

	const ComponentId GetComponentId() const { return _componentId; }
	const EntityId GetOwner() const { return _owner; }

	void SetActive(bool state) { _enabled = state; }
	bool Active() const { return _enabled; }

protected:
	ComponentId		_hashValue;
	ComponentId		_componentId	{ INVALID_COMPONENT_ID };
	EntityId		_owner;
	bool			_enabled		{ true };

private:
	friend class ComponentManager;
};

