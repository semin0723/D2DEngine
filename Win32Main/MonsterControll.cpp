#include "MonsterControll.h"
#include "ECSCall.h"
#include "Components.h"

MonsterControll::MonsterControll()
{
	_spawner = new MonsterSpawner;

	_wayPoint = ResourceSystem::GetInstance()->LoadMonsterWayPoint();

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
	if (_isGameRunning == false) return;

	static float elapseTime;
	elapseTime += dt;
	if (elapseTime >= _spawnInterval) {
		elapseTime -= _spawnInterval;
		_spawner->SpawnMonster();
	}
}

void MonsterControll::Update(float dt)
{
	if (_isGameRunning == false) return;

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
		
		Vector3 targetPos = _wayPoint[_idxInfo[i] + 1];
		float distance = (targetPos - tf->_position).Magnitude();
		if (distance <= 5.0f) {
			if (_idxInfo[i] == 10) {
				ecs->SendEvent<GameObjectDestroyed>(_monsters[i], Object_Layer::Monster);
				if (_spawner->GetCurRound() == 10) {
					ecs->SendEvent<DecreseLife>(50);
					return;
				}
				// life - 1 event
				ecs->SendEvent<DecreseLife>(1);
				continue;
			}
			tf->_position = targetPos;
			tf->_normal = GetNextDir(++_idxInfo[i]);
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
	RegisterCallback(&MonsterControll::OnGamePause);
	RegisterCallback(&MonsterControll::OnGameInitialize);
}

void MonsterControll::UnRegistEvent()
{
	UnRegisterCallback(&MonsterControll::MonsterCreated);
	UnRegisterCallback(&MonsterControll::MonsterDestroyed);
	UnRegisterCallback(&MonsterControll::OnHit);
	UnRegisterCallback(&MonsterControll::OnAreaHit);
	UnRegisterCallback(&MonsterControll::OnGamePause);
	UnRegisterCallback(&MonsterControll::OnGameInitialize);
}

Vector3 MonsterControll::GetNextDir(int curWayPointIdx)
{
	return (_wayPoint[curWayPointIdx + 1] - _wayPoint[curWayPointIdx]).Normalized();
}

void MonsterControll::OnHit(const Attack* event)
{
	for (int i = 0; i < _monsters.size(); i++) {
		if (_monsters[i] == event->_target) {
			MonsterStat* ms = ComponentManager->Getcomponent<MonsterStat>(_monsters[i]);
			Transform* tf = ComponentManager->Getcomponent<Transform>(_monsters[i]);
			ms->_hp -= (std::max)((event->_damage - ms->_defence), 0);
			if (ms->_hp <= 0) {
				ecs->SendEvent<GameObjectDestroyed>(_monsters[i], Object_Layer::Monster);
				
				if (_spawner->GetCurRound() == 10) {
					ecs->SendEvent<GameWin>();
					return;
				}
				// money increse event
				ecs->SendEvent<GetMoney>(Money_Type::Credit, 10);
			}
			return;
		}
	}
}

void MonsterControll::OnAreaHit(const AreaAttack* event)
{
	for (int i = 0; i < _monsters.size(); i++) {
		MonsterStat* ms = ComponentManager->Getcomponent<MonsterStat>(_monsters[i]);
		Transform* tf = ComponentManager->Getcomponent<Transform>(_monsters[i]);
		D2D1_RECT_F monsterBound = GetBounds(tf->_position, tf->_rectSize);
		D2D1_RECT_F attackArea = GetBounds(tf->_position - (tf->_rectSize / 2.0f) + (event->_rectSize / 2.0f), event->_rectSize);

		if (CheckBorder(attackArea, monsterBound) == true) {
			ms->_hp -= (std::max)((event->_damage - ms->_defence), 0);
			if (ms->_hp <= 0) {
				ecs->SendEvent<GameObjectDestroyed>(_monsters[i], Object_Layer::Monster);
				// money increse event
				ecs->SendEvent<GetMoney>(Money_Type::Credit, 10);
			}
		}
	}
}

void MonsterControll::OnGameInitialize(const GameInitialize* event)
{
	_wayPoint = ResourceSystem::GetInstance()->LoadMonsterWayPoint();

	_spawner->SetSpawnPosition(_wayPoint[0]);

	_idxInfo.clear();
	_monsters.clear();
}

void MonsterControll::MonsterCreated(const GameObjectCreated* event)
{
	if (event->_layer != Object_Layer::Monster) return;
	_monsters.push_back(event->_entityId);
	Transform* tf = ComponentManager->Getcomponent<Transform>(event->_entityId);
	tf->_position = _spawner->GetSpawnPosition();

	// curwaypoint idx
	_idxInfo.push_back(0);
}

void MonsterControll::MonsterDestroyed(const GameObjectDestroyed* event)
{
	if (event->_layer != Object_Layer::Monster) return;
	EntityManager->DestroyEntity(event->_entityId);
	for (MonsterInfo::iterator it = _monsters.begin(); it != _monsters.end(); it++) {
		if (*it == event->_entityId) {
			_idxInfo.erase(_idxInfo.begin() + (it - _monsters.begin()));
			_monsters.erase(it);
			break;
		}
	}
}

void MonsterControll::OnGamePause(const GamePause* event)
{
	_isGameRunning ^= true;
}
