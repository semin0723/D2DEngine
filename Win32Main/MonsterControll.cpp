#include "MonsterControll.h"
#include "ECSCall.h"
#include "Components.h"

MonsterControll::MonsterControll() : _wayPoint(4), _dirs(4)
{
	_spawner = new MonsterSpawner;

	_wayPoint[0] = Vector3(31 + 350, 31, 0);
	_wayPoint[1] = Vector3(31 + 350, 829, 0);
	_wayPoint[2] = Vector3(829 + 350, 829, 0);
	_wayPoint[3] = Vector3(829 + 350, 31, 0);

	// idx번 위치로 가는 방향   1 = 0 -> 1
	_dirs[0] = Vector3(-1, 0, 0);
	_dirs[1] = Vector3(0, 1, 0);
	_dirs[2] = Vector3(1, 0, 0);
	_dirs[3] = Vector3(0, -1, 0);

	_spawner->SetSpawnPosition(_wayPoint[0]);

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
	MonsterStat* ms = nullptr;
	for (int i = 0; i < _monsters.size(); i++) {
		tf = ComponentManager->Getcomponent<Transform>(_monsters[i]);
		bc = ComponentManager->Getcomponent<BoxCollider>(_monsters[i]);
		ms = ComponentManager->Getcomponent<MonsterStat>(_monsters[i]);
		if (tf == nullptr || bc == nullptr || ms == nullptr) continue;
		Vector3 dir = tf->_normal;
		tf->_position += dir * ms->_moveSpeed * dt;
		bc->SetBorderLocation(tf->GetTransform());
		
		Vector3 targetPos = GetTargetWayPoint(dir);
		float distance = (targetPos - tf->_position).Magnitude();
		if (distance <= 1.0f) {
			tf->_position = targetPos;
			tf->_normal = GetNextDir(tf->_normal);
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

Vector3& MonsterControll::GetTargetWayPoint(Vector3& normal)
{
	for (int i = 0; i < _dirs.size(); i++) {
		if (normal == _dirs[i]) {
			return _wayPoint[i];
		}
	}
}

Vector3& MonsterControll::GetNextDir(Vector3& curDir)
{
	for (int i = 0; i < _dirs.size(); i++) {
		if (curDir == _dirs[i]) {
			return _dirs[(i + 1) % _dirs.size()];
		}
	}
}

void MonsterControll::OnHit(const Attack* event)
{
	for (int i = 0; i < _monsters.size(); i++) {
		if (_monsters[i] == event->_target) {
			MonsterStat* ms = ComponentManager->Getcomponent<MonsterStat>(_monsters[i]);
			Transform* tf = ComponentManager->Getcomponent<Transform>(_monsters[i]);
			ms->_hp -= (std::max)((event->_damage - ms->_defence), 0);
			ecs->SendEvent<CreateEffect>(L"Hit", tf->_position - Vector3(12.0f, 12.0f, 0));
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
