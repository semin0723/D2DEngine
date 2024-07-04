#include "TowerControll.h"
#include "Components.h"

void TowerControll::RegistEvent()
{
	RegisterCallback(&TowerControll::OnGameObjectCreated);
	RegisterCallback(&TowerControll::OnGameObjectDestroyed);
}

void TowerControll::UnRegistEvent()
{
	UnRegisterCallback(&TowerControll::OnGameObjectCreated);
	UnRegisterCallback(&TowerControll::OnGameObjectDestroyed);
}

void TowerControll::PreUpdate(float dt)
{
	SearchEnemyInRange();
}

void TowerControll::Update(float dt)
{
}

void TowerControll::PostUpdate(float dt)
{
}

void TowerControll::SearchEnemyInRange()
{
	using MonsterDistance = std::pair<float, EntityId>; // distance, entityId
	using MonsterInRange = std::priority_queue<MonsterDistance, std::vector<MonsterDistance>, std::greater<MonsterDistance>>;

	for (int i = 0; i < _towers.size(); i++) {
		MonsterInRange monstersInRange;

		Transform* tfTower = ComponentManager->Getcomponent<Transform>(_towers[i]);
		DetectComponent* dcTower = ComponentManager->Getcomponent<DetectComponent>(_towers[i]);

		Vector3 towerCenterPos = tfTower->_position + (tfTower->_rectSize / 2);
		for (int j = 0; j < _enemies.size(); j++) {
			Transform* tfEnemy = ComponentManager->Getcomponent<Transform>(_enemies[i]);
			Vector3 enemyCenterPos = tfEnemy->_position + (tfEnemy->_rectSize / 2);

			float distance = (enemyCenterPos - towerCenterPos).Magnitude();
			if (distance <= dcTower->_detectRange) {
				monstersInRange.push({ distance, _enemies[i] });
			}
		}

		dcTower->_targetEntity = monstersInRange.top().second;
	}
}

void TowerControll::Attack()
{
}

void TowerControll::OnGameObjectCreated(const GameObjectCreated* event)
{
	if (event->_layer == Object_Layer::Monster) {
		_enemies.push_back(event->_entityId);
	}
	else if (event->_layer == Object_Layer::Player) {
		_towers.push_back(event->_entityId);
	}
}

void TowerControll::OnGameObjectDestroyed(const GameObjectDestroyed* event)
{
	if (event->_layer == Object_Layer::Monster) {
		for (Enemies::iterator it = _enemies.begin(); it != _enemies.end(); it++) {
			if (*it == event->_entityId) {
				_enemies.erase(it);
			}
		}
	}
	else if (event->_layer == Object_Layer::Player) {
		for (Enemies::iterator it = _towers.begin(); it != _towers.end(); it++) {
			if (*it == event->_entityId) {
				_towers.erase(it);
			}
		}
	}
}
