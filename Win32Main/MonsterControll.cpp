#include "MonsterControll.h"
#include "ECSCall.h"
#include "Components.h"

MonsterControll::MonsterControll()
{
	_spawner = new MonsterSpawner;
	RegistEvent();	
}

MonsterControll::~MonsterControll()
{
	delete _spawner;
	UnRegistEvent();
}

void MonsterControll::PreUpdate(float dt)
{
	static float elapseTime;
	elapseTime += dt;
	if (elapseTime >= _spawnInterval) {
		elapseTime -= _spawnInterval;
		_spawner->SpawnMonster();
	}
}

void MonsterControll::Update(float dt)
{
	Transform* tf = nullptr;
	BoxCollider* bc = nullptr;
	for (int i = 0; i < _monsters.size(); i++) {
		tf = ComponentManager->Getcomponent<Transform>(_monsters[i]);
		bc = ComponentManager->Getcomponent<BoxCollider>(_monsters[i]);
		if (tf == nullptr || bc == nullptr) continue;
		tf->_position += Vector3(0, 100, 0) * dt;
		bc->SetBorderLocation(tf->GetTransform());
		if (tf->_position.y >= 800) {
			EntityManager->DestroyEntity(_monsters[i]);
			ecs->SendEvent<GameObjectDestroyed>(_monsters[i], Object_Layer::Monster);
		}
	}
}

void MonsterControll::PostUpdate(float dt)
{
}

void MonsterControll::RegistEvent()
{
	RegisterCallback(&MonsterControll::MonsterCreated);
	RegisterCallback(&MonsterControll::MonsterDestroyed);
	RegisterCallback(&MonsterControll::OnHit);
	RegisterCallback(&MonsterControll::OnAreaHit);
}

void MonsterControll::UnRegistEvent()
{
	UnRegisterCallback(&MonsterControll::MonsterCreated);
	UnRegisterCallback(&MonsterControll::MonsterDestroyed);
	UnRegisterCallback(&MonsterControll::OnHit);
	UnRegisterCallback(&MonsterControll::OnAreaHit);
}

void MonsterControll::OnHit(const Attack* event)
{
	for (int i = 0; i < _monsters.size(); i++) {
		if (_monsters[i] == event->_target) {
			MonsterStat* ms = ComponentManager->Getcomponent<MonsterStat>(_monsters[i]);
			ms->_hp -= (std::max)((event->_damage - ms->_defence), 0);
			// sendEvent<CreateEffect>(); 몬스터 피격 이펙트 출력
			if (ms->_hp <= 0) {
				ecs->SendEvent<GameObjectDestroyed>(_monsters[i], Object_Layer::Monster);
			}
			return;
		}
	}
}

void MonsterControll::OnAreaHit(const AreaAttack* event)
{
}

void MonsterControll::MonsterCreated(const GameObjectCreated* event)
{
	if (event->_layer != Object_Layer::Monster) return;
	_monsters.push_back(event->_entityId);
	Transform* tf = ComponentManager->Getcomponent<Transform>(event->_entityId);
	Sprite* sp = ComponentManager->AddComponent<Sprite>(event->_entityId, L"TestImage");
	BoxCollider* bc = ComponentManager->AddComponent<BoxCollider>(event->_entityId, sp->_spriteSize);
	tf->_position = _spawner->GetSpawnPosition();
}

void MonsterControll::MonsterDestroyed(const GameObjectDestroyed* event)
{
	if (event->_layer != Object_Layer::Monster) return;
	for (MonsterInfo::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if (*it == event->_entityId) {
			_monsters.erase(it);
			break;
		}
	}
}
