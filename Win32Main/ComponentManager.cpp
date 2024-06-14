#include "ComponentManager.h"

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

ComponentId ComponentManager::MappingComponentId(IComponent* component)
{
    return ComponentId();
}

void ComponentManager::ReleaseComponentId(ComponentId id)
{
}

void ComponentManager::MapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId)
{
}

void ComponentManager::UnMapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId)
{
}


