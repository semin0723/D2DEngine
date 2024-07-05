#include "MonsterSpawner.h"
#include "Monster.h"
#include "Components.h"

void MonsterSpawner::RegistEvent()
{
	RegisterCallback(&MonsterSpawner::OnRoundStart);
	RegisterCallback(&MonsterSpawner::OnRoundEnd);
}

void MonsterSpawner::UnRegistEvent()
{
	UnRegisterCallback(&MonsterSpawner::OnRoundStart);
	UnRegisterCallback(&MonsterSpawner::OnRoundEnd);
}

void MonsterSpawner::OnRoundEnd(const RoundEnd* event)
{
	_curRound = _nextRound;
	_nextRound++;
}

void MonsterSpawner::OnRoundStart(const RoundStart* event)
{
}

void MonsterSpawner::SpawnMonster()
{
	if (_spawnCount > 0) {
		_spawnCount--;
		EntityId newEntityId = EntityManager->CreateEntity<Monster>();
		Transform* tf = ComponentManager->AddComponent<Transform>(newEntityId);
		tf->_normal = Vector3(0, 1, 0);
		Sprite* sp = ComponentManager->AddComponent<Sprite>(newEntityId, L"TestImage");
		BoxCollider* bc = ComponentManager->AddComponent<BoxCollider>(newEntityId, sp->_spriteSize);
		MonsterStat* ms = ComponentManager->AddComponent<MonsterStat>(newEntityId, 10, 0, 200);

		ECS::_ecs->SendEvent<GameObjectCreated>(newEntityId, Object_Layer::Monster);
	}
}
