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

	// ������Ʈ�� �������� Ȯ���� �ؽ÷� ����� ������Ʈ�� id������ �Ѵ�.
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

