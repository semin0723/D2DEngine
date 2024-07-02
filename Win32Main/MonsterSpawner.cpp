#include "MonsterSpawner.h"
#include "Monster.h"

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
	EntityId newEntityId = ECS::_ecs->GetEntityManager()->CreateEntity<Monster>();
	IEntity* newEntity = ECS::_ecs->GetEntityManager()->GetEntity(newEntityId);
	static_cast<Monster*>(newEntity)->Initialize();
	ECS::_ecs->SendEvent<GameObjectCreated>(newEntityId, Object_Layer::Monster);
}
