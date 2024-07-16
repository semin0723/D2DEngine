#pragma once
#include "ECSElements.h"
#include "EventListener.h"
#include "globalheader.h"
#include "Camera.h"
#include "Events.h"


struct tileInfo {
	Tile_State _tileState; 
	Tower_Type _towerType;
	EntityId _towerId;
	UINT _towerGrade;
	tileInfo() {
		_tileState = Tile_State::Default;
		_towerType = Tower_Type::Default;
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
	void OnLifeDecrese(const DecreseLife* event);
	void OnGetMoney(const GetMoney* event);

private:
	std::vector<std::vector<tileInfo>> _mapdata;
	UINT _actionState = 0;

	void InitialGame();

	void RegistEvent();
	void UnRegistEvent();

	// 1 : createTower    2 : MergeTower     3 : DeleteTower
	void EnterCreateState() { if (_isGameRunning) _actionState = 1; }
	void EnterMergeState()	{ if (_isGameRunning) _actionState = 2; }
	void EnterDeleteState() { if (_isGameRunning) _actionState = 3; }

	Vector3 _tileoffset	{ 50.0f, 75.0f, 0 };
	float _sizePerTile = 106.0f;
	std::pair<int, int> ConvertClickToIdx(const Vector3& clickLoc);
	Vector3 ConvertIdxToTile(std::pair<int, int>& idx);

	void SetTileInfo(const std::pair<int, int>& idx, Tile_State state, Tower_Type type, const EntityId& towerId, UINT grade);
	EntityId CreateTower(const Vector3& loc, UINT towerGrade);
	void DeleteTower(const std::pair<int, int>& idx);

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

	EntityId MoneyArea();
	EntityId LifeArea();
	EntityId ButtonArea();

	EntityId PauseArea();

private:
	// 인게임 로직 관련 부분
	int _life = 50;
	EntityId _lifeText;

	int _money = 100;
	EntityId _moneyText;

	bool _isGameRunning = true;
	EntityId _pauseUIGroup;
	void Pause();
	void Resume();
};

