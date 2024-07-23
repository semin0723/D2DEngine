#pragma once
#include "ECSElements.h"
#include "EventListener.h"
#include "globalheader.h"
#include "Events.h"
#include "MonsterSpawner.h"

class MonsterControll : public System<MonsterControll>, public EventListener
{
public:
	MonsterControll();
	~MonsterControll();

	virtual void PreUpdate(float dt);
	virtual void Update(float dt);
	virtual void PostUpdate(float dt);

	void RegistEvent();
	void UnRegistEvent();

	Vector3 GetNextDir(int curWayPointIdx);

	void OnHit(const Attack* event);
	void OnAreaHit(const AreaAttack* event);

	void OnGameInitialize(const GameInitialize* event);

	void MonsterCreated(const GameObjectCreated* event);
	void MonsterDestroyed(const GameObjectDestroyed* event);
	void OnGamePause(const GamePause* event);
	

private:
	using MonsterInfo = std::vector<EntityId>;
	using WayPoint = std::vector<Vector3>;
	using MonsterWayPointIdxInfo = std::vector<int>;

	MonsterWayPointIdxInfo _idxInfo;
	WayPoint _wayPoint;
	MonsterInfo _monsters;
	MonsterSpawner* _spawner = nullptr;
	float _spawnInterval = 1.0f;

	bool _isGameRunning = true;
};

