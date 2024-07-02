#pragma once
#include "utilheader.h"
#include "EntityHandleTable.h"
#include "IEntity.h"
#include "ComponentManager.h"
#include "ECSBase.h"

class EntityManager
{
	class IEntityContainer {
	public:
		virtual ~IEntityContainer() {}
		virtual const std::string GetEntityContainerType() const = 0;
		virtual void CreateObject(IEntity* entity) = 0;
		virtual void DestroyEntity(IEntity* entity) = 0;
	};

	template<class T>
	class EntityContainer : public IEntityContainer {
		EntityContainer(const EntityContainer&) = delete;
		EntityContainer& operator=(EntityContainer&) = delete;

		using EntityList = std::list<IEntity*>;

	public:
		EntityContainer() {}
		virtual ~EntityContainer() {}

		virtual const std::string GetEntityContainerType() const {
			static const std::string ENTITY_TYPE	{ typeid(T).name() };
			return ENTITY_TYPE;
		}

		virtual void CreateObject(IEntity* entity) {
			_entities.push_back(entity);
		}

		virtual void DestroyEntity(IEntity* entity) {
			EntityList::iterator it;
			for (EntityList::iterator i = _entities.begin(); i != _entities.end(); i++) {
				if (entity->GetEntityId() == (*i)->GetEntityId()) {
					it = i;
					break;
				}
			}
			if (it != _entities.end()) {
				_entities.erase(it);
				delete entity;
			}
		}

	private:
		EntityList _entities;
	};

	using HandleTable = EntityHandleTable<IEntity, EntityId>;
	using EntityRegistry = std::unordered_map<EntityTypeId, IEntityContainer*>;

public:
	EntityManager(ComponentManager* componentManagerInstance);
	~EntityManager();

	template<class T, class... ARGS>
	EntityId CreateEntity(ARGS&&... args) {
		IEntity* newEntity = new T(std::forward<ARGS>(args)...);

		EntityId entityId = MappingEntityId(newEntity);
		newEntity->_entityId = entityId;
		newEntity->_componentManagerInstance = _componentManagerInstance;
		GetEntityContainer<T>()->CreateObject(newEntity);

		return entityId;
	}

	void DestroyEntity(EntityId id) {
		IEntity* entity = _entityHandleTable[id];

		const EntityTypeId tid = entity->GetEntityTypeId();
		if (_pendingDestroyEntityCount < _pendingDestroyEntities.size()) {
			_pendingDestroyEntities[_pendingDestroyEntityCount++] = id;
		}
		else {
			_pendingDestroyEntities.push_back(id);
			_pendingDestroyEntityCount++;
		}
	}

	IEntity* GetEntity(EntityId id) {
		return _entityHandleTable[id];
	}

	EntityId GetEntityId(ULL idx) {
		return _entityHandleTable[idx];
	}

	void RemoveDestroyEntities();

private:
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(EntityManager&) = delete;

	HandleTable _entityHandleTable;

	EntityRegistry _entityRegistry;

	std::vector<EntityId> _pendingDestroyEntities;
	ULL _pendingDestroyEntityCount;

	ComponentManager* _componentManagerInstance;

	template<class T>
	EntityContainer<T>* GetEntityContainer() {
		EntityTypeId eid = T::ENTITY_TYPE_ID;
		EntityContainer<T>* entityContainer = nullptr;

		auto iterator = _entityRegistry.find(eid);
		if (iterator == _entityRegistry.end()) {
			entityContainer = new EntityContainer<T>;
			_entityRegistry[eid] = entityContainer;
		}
		else {
			entityContainer = (EntityContainer<T>*)iterator->second;
		}
		return entityContainer;
	}

	EntityId MappingEntityId(IEntity* entity);
	void ReleaseEntityId(EntityId id);
};

