#include "EntityManager.h"

EntityManager::EntityManager(ComponentManager* componentManagerInstance) :
	_pendingDestroyEntities(1024),
	_pendingDestroyEntityCount(0),
	_componentManagerInstance(componentManagerInstance)
{
}

EntityManager::~EntityManager()
{
	for(auto entityContainer : _entityRegistry){
		delete entityContainer.second;
		entityContainer.second = nullptr;
	}
}

void EntityManager::RemoveDestroyEntities()
{
	for (size_t i = 0; i < _pendingDestroyEntityCount; i++)
	{
		EntityId id = _pendingDestroyEntities[i];
		IEntity* entity = _entityHandleTable[id];

		if (entity == nullptr) continue;
		const EntityTypeId tid = entity->GetEntityTypeId();

		auto iterator = _entityRegistry.find(tid);
		if (iterator != _entityRegistry.end()) {
			_componentManagerInstance->RemoveAllComponents(id);
			iterator->second->DestroyEntity(entity);
		}
		ReleaseEntityId(id);
	}
	_pendingDestroyEntityCount = 0;
}

EntityId EntityManager::MappingEntityId(IEntity* entity)
{
    return _entityHandleTable.MappingHandle(entity);
}

void EntityManager::ReleaseEntityId(EntityId id)
{
    _entityHandleTable.ReleaseHandle(id);
}
