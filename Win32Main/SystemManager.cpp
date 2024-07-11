#include "SystemManager.h"
#include "ISystem.h"

SystemManager::SystemManager()
{

}

SystemManager::~SystemManager()
{
	for (SystemOrder::reverse_iterator it = _workOrder.rbegin(); it != _workOrder.rend(); it++) {
		if(*it != nullptr) delete (*it);
		*it = nullptr;
	}
	_workOrder.clear();
	_systems.clear();
}

void SystemManager::Update(float dt)
{
	for (ISystem* system : _workOrder) {
		system->_lastUpdateTime += dt;

		// updateinterval < 0  -> ��� ������Ʈ, �Ǵ� updateinterval < lastupdate ������Ʈ ���� �ð��� ������Ʈ �ֱ⺸�� ũ��
		system->_canUpdate = (system->_updateInterval < 0.0f) || ((system->_updateInterval > 0.0f) && (system->_updateInterval < system->_lastUpdateTime));

		if (system->_enabled && system->_canUpdate) {
			system->PreUpdate(dt);
		}
	}
	for (ISystem* system : _workOrder) {
		if (system->_enabled && system->_canUpdate) {
			system->Update(dt);

			system->_lastUpdateTime = 0.0f;
		}
	}
	for (ISystem* system : _workOrder) {
		if (system->_enabled && system->_canUpdate) {
			system->PostUpdate(dt);
		}
	}
}
