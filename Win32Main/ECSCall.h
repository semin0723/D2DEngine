#pragma once
#include "ECSBase.h"
class ECSBase;

namespace ECS {
	extern ECSBase* _ecs;

	void Initialize();
	void Finalize();
}
