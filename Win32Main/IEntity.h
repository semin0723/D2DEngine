#pragma once
#include "EntityHandleTable.h"
#include "FamilyTypeId.h"
#include "ComponentManager.h"

using EntityTypeId	= TypeId;
using ChildEntities = std::vector<EntityId>;

// 엔티티의 id의 invalid값도 handle의 invalid값과 같은 값으로 설정합니다.
static const ULL INVALID_ENTITY_ID = (std::numeric_limits<ULL>::max)();

class IEntity
{
public:
	IEntity();
	virtual ~IEntity() {}

	template<class T>
	T* GetComponent() const { return _componentManagerInstance->Getcomponent<T>(_entityId); }

	template<class T, class ...P>
	T* AddComponent(P&&... param) { return _componentManagerInstance->AddComponent<T>(_entityId, std::forward<P>(param)...); }

	template<class T>
	void RemoveComponent() { _componentManagerInstance->RemoveComponent<T>(_entityId); }

	// 엔티티 끼리의 비교, 언젠간 사용할듯?  포인터로 받아서 비교와 참조로 받아서 비교 두개를 만든다.
	bool operator==(const IEntity& other) const { return _entityId == other._entityId; }
	bool operator!=(const IEntity& other) const { return _entityId != other._entityId; }
	bool operator==(const IEntity* other) const { return _entityId == other->_entityId; }
	bool operator!=(const IEntity* other) const { return _entityId != other->_entityId; }

	virtual const EntityTypeId GetEntityTypeId() const = 0;
	const EntityId GetEntityId() const { return _entityId; }

	void SetParentEntity(EntityId id) { _parent = id; }
	void AddChildEntity(EntityId id) { _childs.push_back(id); }
	const EntityId GetParentEntityId() const { return _parent; }
	const ChildEntities& GetChildEntityId() const{ return _childs; }

	// 설정할 state의 상태에 따라 해당 엔티티를 보이게 할거냐 숨길거냐를 설정하는 곳.
	void SetActive(bool state);
	bool Active() const { return _active; }

	virtual void OnEnable() {}
	virtual void OnDisable() {}

protected:

	// EntityManager에서 id를 생성해야 합니다.
	EntityId	_entityId;

	EntityId	_parent;
	ChildEntities _childs;

	bool		_active;

private:
	ComponentManager* _componentManagerInstance;

	friend class EntityManager;
};

