#include "MonsterSpawner.h"
#include "Monster.h"
#include "Components.h"
#include "ResourceSystem.h"

MonsterSpawner::MonsterSpawner() : _spawnPosition(Vector3(500, 100, 0)) 
{
	RegistEvent(); 
}

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

}

void MonsterSpawner::OnRoundStart(const RoundStart* event)
{
	if (_nextRound > 10) return;
	_curRound = _nextRound;
	_nextRound++;
	_spawnCount = ResourceSystem::GetInstance()->GetMonsterInfo(_curRound)._spawnCountPerRound;
}

void MonsterSpawner::SpawnMonster()
{
	if (_spawnCount > 0) {
		MonsterInfo roundinfo = ResourceSystem::GetInstance()->GetMonsterInfo(_curRound);

		_spawnCount--;
		EntityId newEntityId = EntityManager->CreateEntity<Monster>();
		Transform* tf = ComponentManager->AddComponent<Transform>(newEntityId);
		tf->_normal = Vector3(0, 1, 0);
		Sprite* sp = ComponentManager->AddComponent<Sprite>(newEntityId, roundinfo._imageDirectory);
		tf->_rectSize = Vector3(40, 40, 0);
		BoxCollider* bc = ComponentManager->AddComponent<BoxCollider>(newEntityId, Vector3(40, 40, 0));
		MonsterStat* ms = ComponentManager->AddComponent<MonsterStat>(newEntityId, roundinfo._hp, roundinfo._defence, roundinfo._moveSpeed);

		ECS::_ecs->SendEvent<GameObjectCreated>(newEntityId, Object_Layer::Monster);
	}
	if (_spawnCount == 0) {
		ecs->SendEvent<RoundEnd>();
		_spawnCount = -1;
	}
}
