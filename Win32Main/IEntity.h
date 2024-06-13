#pragma once
#include "Handle.h"

using EntityTypeId	= TypeId;
using EntityId		= Handle64;

// 엔티티의 id의 invalid값도 handle의 invalid값과 같은 값으로 설정합니다.
static const EntityId INVALID_ENTITY_ID = Handle64::INVALID_HANDLE;

class IEntity
{
public:
	IEntity();
	virtual ~IEntity() {}

	template<class T>
	T* GetComponent() const {}

	template<class T, class ...P>
	T* AddComponent(P&&... param) {}

	template<class T>
	void RemoveComponent() {}

	// 엔티티 끼리의 비교, 언젠간 사용할듯?  포인터로 받아서 비교와 참조로 받아서 비교 두개를 만든다.
	bool operator==(const IEntity& other) const { return _entityId == other._entityId; }
	bool operator!=(const IEntity& other) const { return _entityId != other._entityId; }
	bool operator==(const IEntity* other) const { return _entityId == other->_entityId; }
	bool operator!=(const IEntity* other) const { return _entityId != other->_entityId; }

	virtual const EntityTypeId GetEntityTypeId() const = 0;
	const EntityId GetEntityId() const { return _entityId; }

	// 설정할 state의 상태에 따라 해당 엔티티를 보이게 할거냐 숨길거냐를 설정하는 곳.
	void SetActive(bool state);
	bool Active() const { return _active; }

	virtual void OnEnable() {}
	virtual void OnDisable() {}

protected:
	// EntityManager에서 id를 생성해야 합니다.
	EntityId	_entityId;

	bool		_active;

private:
	// ComponentManager* _componentManagerInstance;

	friend class EntityManager;
};

