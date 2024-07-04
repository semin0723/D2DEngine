#include "TowerControll.h"
#include "Components.h"
#include "Events.h"

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
}

void TowerControll::Update(float dt)
{
	// Ž��
	SearchEnemyInRange();

	// ȸ��
	for (int i = 0; i < _towers.size(); i++) {
		Transform* tfTower = ComponentManager->Getcomponent<Transform>(_towers[i]);
		DetectComponent* dcTower = ComponentManager->Getcomponent<DetectComponent>(_towers[i]);

		if (dcTower->_targetEntity._index == (std::numeric_limits<ULL>::max)()) continue;

		Vector3 towerCenterPos = GetCenterPos(_towers[i]);
		Vector3 targetCenterPos = GetCenterPos(dcTower->_targetEntity);
		Vector3 targetDir = targetCenterPos - towerCenterPos;
		tfTower->CalcRotation(targetDir);
	}

	//����
	//EnemyAttack();
}

void TowerControll::PostUpdate(float dt)
{
}

void TowerControll::SearchEnemyInRange()
{
	using MonsterDistance = std::pair<float, EntityId>; // distance, entityId
	using MonsterInRange = std::priority_queue<MonsterDistance, std::vector<MonsterDistance>, compare>;
	 
	for (int i = 0; i < _towers.size(); i++) {
		MonsterInRange monstersInRange;

		DetectComponent* dcTower = ComponentManager->Getcomponent<DetectComponent>(_towers[i]);

		Vector3 towerCenterPos = GetCenterPos(_towers[i]);
		for (int j = 0; j < _enemies.size(); j++) {
			Vector3 enemyCenterPos = GetCenterPos(_enemies[j]);
			float distance = (enemyCenterPos - towerCenterPos).Magnitude();
			if (distance <= dcTower->_detectRange) {
				// ������ ��ϵ� Ÿ���� ���� ���� ������ �����ϴ°�.
				if (_enemies[j] == dcTower->_targetEntity) return;
				monstersInRange.push({ distance, _enemies[j] });
			}
		}

		if (!monstersInRange.empty()) {
			dcTower->_targetEntity = monstersInRange.top().second;
		}
		else {
			dcTower->_targetEntity = EntityId((std::numeric_limits<ULL>::max)(), (std::numeric_limits<ULL>::max)());
		}
	}
}

void TowerControll::EnemyAttack()
{
	for (int i = 0; i < _towers.size(); i++) {
		AttackComponent* ac = ComponentManager->Getcomponent<AttackComponent>(_towers[i]);
		DetectComponent* dc = ComponentManager->Getcomponent<DetectComponent>(_towers[i]);
		if (ac->_multiAttack == false) {
			ecs->SendEvent<Attack>(dc->_targetEntity, ac->_damage);
		}
		else {
			ecs->SendEvent<AreaAttack>(dc->_targetEntity, ac->_damage, ac->_attackRect);
		}
	}
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
			if ((*it) == event->_entityId) {
				_enemies.erase(it);
				break;
			}
		}
	}
	else if (event->_layer == Object_Layer::Player) {
		for (Enemies::iterator it = _towers.begin(); it != _towers.end(); it++) {
			if (*it == event->_entityId) {
				_towers.erase(it);
				break;
			}
		}
	}
}

Vector3 TowerControll::GetCenterPos(EntityId eid)
{
	Transform* tf = ComponentManager->Getcomponent<Transform>(eid);

	return tf->_position + (tf->_rectSize / 2.0f);
}
