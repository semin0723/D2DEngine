#pragma once
#include "utilheader.h"
#include "IComponent.h"
#include "IEntity.h"

template<class Object_Type>
class DataContainer
{
	using Objects = std::vector<Object_Type*>;
	using Iterator = Objects::iterator;

	int ADD_SIZE = 10;

public:
	DataContainer() : _dataContainer(ADD_SIZE, nullptr) {}
	~DataContainer() {
		for (Iterator it = _dataContainer.begin(); it != _dataContainer.end(); it++) {
			delete it;
		}
	}

	void* CreateObject() {
		void* data = it;
		for (Iterator it = _dataContainer.begin(); it != _dataContainer.end(); it++) {
			data = it;
			if (data == nullptr) {
				break;
			}
		}

		if (it != nullptr) {
			_dataContainer.resize(_dataContainer.size() + ADD_SIZE, nullptr);
		}

		for (Iterator it = _dataContainer.begin(); it != _dataContainer.end(); it++) {
			data = it;
			if (data == nullptr) {
				break;
			}
		}

		return data;
	}
	void DestroyObject(IComponent* object) {

	}

	void DestroyObject(IEntity* object) {

	}

private:
	Objects _dataContainer;
};

