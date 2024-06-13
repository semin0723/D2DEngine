#pragma once
#include "Handle.h"

using EntityTypeId	= TypeId;
using EntityId		= Handle64;

// ��ƼƼ�� id�� invalid���� handle�� invalid���� ���� ������ �����մϴ�.
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

	// ��ƼƼ ������ ��, ������ ����ҵ�?  �����ͷ� �޾Ƽ� �񱳿� ������ �޾Ƽ� �� �ΰ��� �����.
	bool operator==(const IEntity& other) const { return _entityId == other._entityId; }
	bool operator!=(const IEntity& other) const { return _entityId != other._entityId; }
	bool operator==(const IEntity* other) const { return _entityId == other->_entityId; }
	bool operator!=(const IEntity* other) const { return _entityId != other->_entityId; }

	virtual const EntityTypeId GetEntityTypeId() const = 0;
	const EntityId GetEntityId() const { return _entityId; }

	// ������ state�� ���¿� ���� �ش� ��ƼƼ�� ���̰� �Ұų� ����ųĸ� �����ϴ� ��.
	void SetActive(bool state);
	bool Active() const { return _active; }

	virtual void OnEnable() {}
	virtual void OnDisable() {}

protected:
	// EntityManager���� id�� �����ؾ� �մϴ�.
	EntityId	_entityId;

	bool		_active;

private:
	// ComponentManager* _componentManagerInstance;

	friend class EntityManager;
};

