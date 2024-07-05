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

	Vector3& GetTargetWayPoint(Vector3& normal);
	Vector3& GetNextDir(Vector3& curDir);

	void OnHit(const Attack* event);
	void OnAreaHit(const AreaAttack* event);

	void MonsterCreated(const GameObjectCreated* event);
	void MonsterDestroyed(const GameObjectDestroyed* event);
private:
	using MonsterInfo = std::vector<EntityId>;
	using WayPoint = std::vector<Vector3>;
	using MoveDir = std::vector<Vector3>;

	MoveDir _dirs;
	WayPoint _wayPoint;
	MonsterInfo _monsters;
	MonsterSpawner* _spawner = nullptr;
	float _spawnInterval = 1.0f;
};

