#pragma once
#include "utilheader.h"
#include "IComponent.h"



class ComponentManager
{
	class IComponentContainer {
	public:
		virtual ~IComponentContainer() {}

		virtual const char* GetComponentContainerTypeName() const = 0;
		virtual void DestroyComponent(IComponent* component) = 0;
	};

	// ������Ʈ �����̳ʸ� �޸�ûũ�� Ȱ���Ͽ� ������ �ؾ� �ϴµ� �޸�ûũ�� ���ؼ��� ����� �ƴ� ���� ���� ������
	// �޸�ûũ ��� ����Ʈ�� ���͸� Ȱ���Ͽ� ������ �õ��� ����. // vector.resize() -> �̹� ä���� �ִ� �����ʹ� ������� �ø� �������� ���� �����Ͱ� ä������.
	// ������Ʈ���� �����ϴ� ����Ʈ�� Ŭ���� ���·� �����Ͽ� ��� �޾ƾ���.
	template<class T>
	class ComponentContainer : public DataContainer<T>, public IComponentContainer {
		ComponentContainer(const ComponentContainer&) = delete;
		ComponentContainer& operator=(ComponentContainer&) = delete;
	public:
		ComponentContainer() {}
		virtual ~ComponentContainer() {}

		// ������Ʈ�� ��ӹ޴� Ŭ������ �̸��� �����ɴϴ�.
		virtual const char* GetComponentContainerTypeName() const override {
			static const char* ComponentTypeName	{ typeid(T).name() };
			return ComponentTypeName;
		}

		virtual void DestroyComponent(IComponent* component) override {
			component->~IComponent();

			//Component�� �����ؾ���.
		}

		// ���⿡ Ÿ�Ժ� �����̳ʸ� ��Ƽ� �����ϰ� �Ѵ�.
	};

	ComponentManager(const ComponentManager&) = delete;
	ComponentManager& operator=(ComponentManager&) = delete;

	using ComponentContainerRegistry = std::unordered_map<ComponentTypeId, IComponentContainer*>;

	ComponentContainerRegistry _componentContainerRegistry;

	// ������Ʈ ������ ���� ������Ʈ �����̳ʸ� ��ȯ�մϴ�.
	template<class T>
	ComponentContainer<T>* GetComponentContainer() {
		ComponentTypeId componentId = T::COMPONENT_TYPE_ID;

		auto iterator = _componentContainerRegistry.find(componentId);

		ComponentContainer<T>* componentContainer = nullptr;

		if (iterator == _componentContainerRegistry.end()) {
			componentContainer = new ComponentContainer<T>;
			_componentContainerRegistry[componentId] = componentContainer;
		}
		else {
			componentContainer = static_cast<ComponentContainer<T>*>(iterator->second);
		}

		return componentContainer;
	}

	
	using ComponentTable = std::vector<IComponent*>;
	// ������Ʈ���� ��Ƶδ� ���̺�.
	ComponentTable _componentTable;
	
	using EntityComponentMap = std::vector<std::vector<ComponentId>>;
	// �ϳ��� ��ƼƼ �ȿ� ����ִ� ������Ʈ�� Id���� ���̺�.
	EntityComponentMap _entityComponentMap;

	ComponentId MappingComponentId(IComponent* component);
	void		ReleaseComponentId(ComponentId id);

	void		MapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);
	void		UnMapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);

public:
	// ComponentContainer ���� ���� ������ �� iterator�� ���� �����������.
	template<class T>
	using TComponentIterator = typename ComponentContainer<T>::iterator;

	ComponentManager();
	~ComponentManager();

	template<class T, class ...ARGS>
	T* AddComponent(const EntityId entityId, ARGS&&... args) {
		static constexpr std::hash<ComponentId> ENTITY_COMPONENT_ID_HASHER	{ std::hash<ComponentId> };

		const ComponentTypeId typeId = T::COMPONENT_TYPE_ID;

		IComponent* newComponent = new T(std::forward<ARGS>(args)...);

		newComponent->_owner = entityId;
		return newComponent;
	}

private:


	friend class IComponent;
};

