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

	// 컴포넌트 컨테이너를 메모리청크를 활용하여 관리를 해야 하는데 메모리청크에 대해서는 제대로 아는 것이 없기 때문에
	// 메모리청크 대신 리스트나 벡터를 활용하여 관리를 시도할 예정. // vector.resize() -> 이미 채워져 있는 데이터는 상관없이 늘린 공간에만 새로 데이터가 채워진다.
	// 컴포넌트들을 관리하는 리스트를 클래스 형태로 제작하여 상속 받아야함.
	template<class T>
	class ComponentContainer : public DataContainer<T>, public IComponentContainer {
		ComponentContainer(const ComponentContainer&) = delete;
		ComponentContainer& operator=(ComponentContainer&) = delete;
	public:
		ComponentContainer() {}
		virtual ~ComponentContainer() {}

		// 컴포넌트를 상속받는 클래스의 이름을 가져옵니다.
		virtual const char* GetComponentContainerTypeName() const override {
			static const char* ComponentTypeName	{ typeid(T).name() };
			return ComponentTypeName;
		}

		virtual void DestroyComponent(IComponent* component) override {
			component->~IComponent();

			//Component를 삭제해야함.
		}

		// 여기에 타입별 컨테이너를 모아서 관리하게 한다.
	};

	ComponentManager(const ComponentManager&) = delete;
	ComponentManager& operator=(ComponentManager&) = delete;

	using ComponentContainerRegistry = std::unordered_map<ComponentTypeId, IComponentContainer*>;

	ComponentContainerRegistry _componentContainerRegistry;

	// 컴포넌트 유형에 따른 컴포넌트 컨테이너를 반환합니다.
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
	// 컴포넌트들을 모아두는 테이블.
	ComponentTable _componentTable;
	
	using EntityComponentMap = std::vector<std::vector<ComponentId>>;
	// 하나의 엔티티 안에 들어있는 컴포넌트의 Id들의 테이블.
	EntityComponentMap _entityComponentMap;

	ComponentId MappingComponentId(IComponent* component);
	void		ReleaseComponentId(ComponentId id);

	void		MapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);
	void		UnMapEntityComponent(EntityId entityId, ComponentId componentId, ComponentTypeId componentTypeId);

public:
	// ComponentContainer 내부 구조 설정할 때 iterator도 같이 설정해줘야함.
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

