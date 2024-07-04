#pragma once
#include "ECSBase.h"

#define ecs ECS::_ecs
#define SystemManager ecs->GetSystemManager()
#define EntityManager ecs->GetEntityManager()
#define ComponentManager ecs->GetComponentManager()

class ECSBase;

namespace ECS {
	extern ECSBase* _ecs;

	void Initialize();
	void Finalize();
}
