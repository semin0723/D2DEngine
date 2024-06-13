#pragma once
#include "IComponent.h"

template<class T>
class Component : public IComponent
{
public:
	static const ComponentTypeId COMPONENT_TYPE_ID;

	Component() {}
	virtual ~Component() {}
	
	ComponentTypeId GetComponentTypeId() const { return COMPONENT_TYPE_ID; }
};

template<class T>
const ComponentTypeId Component<T>::COMPONENT_TYPE_ID = FamilyTypeId<IComponent>::Get<T>();

