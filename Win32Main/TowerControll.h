#pragma once
#include "ECSElements.h"
#include "globalheader.h"
#include "EventListener.h"
#include "Events.h"

class TowerControll : public System<TowerControll>, public EventListener
{
public:
	TowerControll() { RegistEvent(); }
	~TowerControll() { UnRegistEvent(); }

	void RegistEvent();
	void UnRegistEvent();

	virtual void PreUpdate(float dt);
	virtual void Update(float dt);
	virtual void PostUpdate(float dt);

	void SearchEnemyInRange();
	void Attack();

	void OnGameObjectCreated(const GameObjectCreated* event);
	void OnGameObjectDestroyed(const GameObjectDestroyed* event);
private:
	using Enemies = std::vector<EntityId>;
	using Towers = std::vector<EntityId>;

	Enemies _enemies;
	Towers _towers;

	Vector3 GetCenterPos(EntityId eid);
};

struct compare {
	bool operator()(const std::pair<float, EntityId>& a, const std::pair<float, EntityId>& b) {
		return a.first > b.first;
	}
};

