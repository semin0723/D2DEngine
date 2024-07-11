#pragma once
#include "ECSElements.h"
#include "EventListener.h"
#include "globalheader.h"
#include "Camera.h"
#include "Events.h"

struct tileInfo {
	Tile_State _tileState; 
	EntityId _towerId;
	UINT _towerGrade;
	tileInfo() {
		_tileState = Tile_State::Default;
		_towerId = EntityId();
		_towerGrade = 0;
	}
};

class World : public System<World>, public EventListener
{
public:
	World();
	~World();

	virtual void PreUpdate(float dt);
	virtual void Update(float dt);
	virtual void PostUpdate(float dt);

	Camera* _mainCamera;

	void OnMapClick(const ClickInGame* event);

private:
	std::vector<std::vector<tileInfo>> _mapdata;
	UINT _actionState = 0;

	void InitialGame();

	void RegistEvent();
	void UnRegistEvent();

	void EnterCreateState() { _actionState = 1; }

	Vector3 _tileoffset	{ 50.0f, 75.0f, 0 };
	float _sizePerTile = 106.0f;
	std::pair<int, int> ConvertClickToIdx(const Vector3& clickLoc);
	Vector3 ConvertIdxToTile(std::pair<int, int>& idx);

	EntityId CreateTower(const Vector3& loc);

	template<class E>
	EntityId CreateGameObject(Object_Layer layer) {
		EntityId eid = ECS::_ecs->GetEntityManager()->CreateEntity<E>();
		ECS::_ecs->SendEvent<GameObjectCreated>(eid, layer);
		return eid;
	}

	template<class E>
	EntityId CreateUIObject() {
		EntityId eid = ECS::_ecs->GetEntityManager()->CreateEntity<E>();
		return eid;
	}
};

