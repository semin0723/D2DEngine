#include "ECSCall.h"
#include "ECSBase.h"
namespace ECS {
	ECSBase* _ecs = nullptr;

	void Initialize()
	{
		if (_ecs == nullptr) {
			_ecs = new ECSBase;
		}
	}

	void Finalize()
	{
		if (_ecs != nullptr) {
			delete _ecs;
			_ecs = nullptr;
		}
	}
}

