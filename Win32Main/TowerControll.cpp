#include "TowerControll.h"

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
	for (int i = 0; i < _towers.size(); i++) {

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
