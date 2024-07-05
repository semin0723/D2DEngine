#pragma once
#include "utilheader.h"
#include "ISystem.h"
#include "FamilyTypeId.h"
#include "ECSBase.h"


class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	template<class T, class... ARGS>
	T* AddSystem(ARGS&&... systemArgs) {
		const ULL tid = T::SYSTEM_TYPE_ID;

		auto iterator = _systems.find(tid);
		// 추가하려는 시스템이 이미 존재한다.
		if ((iterator != _systems.end()) && (iterator->second != nullptr)) {
			return (T*)iterator->second;
		}

		T* newSystem = new T(std::forward<ARGS>(systemArgs)...);
		newSystem->_systemManager = this;
		_systems[tid] = newSystem;

		_workOrder.push_back(newSystem);

		return newSystem;
	}

	template<class T>
	void SetSystemEnable(bool state) {
		const SystemTypeId tid = T::SYSTEM_TYPE_ID;

		auto iterator = _systems.find(tid);
		if (iterator != _systems.end()) {
			if (iterator->second->_enabled == state) {
				return;
			}
			iterator->second->_enabled = state;
		}
	}

	template<class T>
	void SetSystemUpdateInverval(float intervalTime) {
		const SystemTypeId tid = T::SYSTEM_TYPE_ID;

		auto iterator = _systems.find(tid);
		if (iterator != _systems.end()) {
			iterator->second->_updateInterval = intervalTime;
		}
	}

private:
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(SystemManager&) = delete;

	using SystemOrder = std::vector<ISystem*>;
	using SystemRegistry = std::unordered_map<ULL, ISystem*>;

	SystemOrder _workOrder;
	SystemRegistry _systems;

	void Update(float dt);

	friend class ECSBase;
};

