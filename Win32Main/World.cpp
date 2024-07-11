#include "World.h"
#include "ECSCall.h"
#include "Square.h"
#include "SampleButton.h"
#include "DefaultUIObject.h"
#include "Components.h"

World::World()
{
	RegistEvent();
	_mainCamera = new Camera;

	InitialGame();

	EntityId			square				= CreateGameObject<Square>(Object_Layer::Player);
	Transform*			tf					= ComponentManager->AddComponent<Transform>(square, Vector3(262.0f, 287.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				sp					= ComponentManager->AddComponent<Sprite>(square, L"Images\\TowerTest");
	BoxCollider*		bc					= ComponentManager->AddComponent<BoxCollider>(square, sp->_spriteSize);
	DetectComponent*	dc					= ComponentManager->AddComponent<DetectComponent>(square, 400.0f);
	AttackComponent*	at					= ComponentManager->AddComponent<AttackComponent>(square, 50, 0.5f);
	tf->SetRectSize(sp->_spriteSize);
	ecs->SendEvent<RegistPlayer>(square);

	EntityId			bg					= CreateGameObject<Square>(Object_Layer::Background);
	Transform*			tfbg				= ComponentManager->AddComponent<Transform>(bg, Vector3(25.0f, 50.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbg				= ComponentManager->AddComponent<Sprite>(bg, L"Images\\TestBg");
	BoxCollider*		bcbg				= ComponentManager->AddComponent<BoxCollider>(bg, spbg->_spriteSize);
	tfbg->SetRectSize(spbg->_spriteSize);

	EntityId			uigroup1			= CreateGameObject<Square>(Object_Layer::UI);
	UITransform*		uitf				= ComponentManager->AddComponent<UITransform>(uigroup1);
	UIGroup*			uig					= ComponentManager->AddComponent<UIGroup>(uigroup1);
	
	EntityId			uibuttonpannel		= CreateUIObject<DefaultUIObject>();
	UITransform*		panneltf			= ComponentManager->AddComponent<UITransform>(uibuttonpannel, Vector3(1150.0f, 750.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannelsp			= ComponentManager->AddComponent<Sprite>(uibuttonpannel, L"Images\\UIPannel");
	panneltf->_size = Vector3(400.0f, 400.0f, 0);

	EntityId			uimoneypannel		= CreateUIObject<DefaultUIObject>();
	UITransform*		pannel2tf			= ComponentManager->AddComponent<UITransform>(uimoneypannel, Vector3(1150.0f, 50.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannel2sp			= ComponentManager->AddComponent<Sprite>(uimoneypannel, L"Images\\UIPannel");
	pannel2tf->_size = Vector3(400.0f, 100.0f, 0);

	EntityId			uibtn				= CreateUIObject<SampleButton>();
	UITransform*		btntf				= ComponentManager->AddComponent<UITransform>(uibtn, Vector3(50.0f, 250.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn				= ComponentManager->AddComponent<Sprite>(uibtn, L"Images\\Button\\ButtonNormal");
	ButtonComponent*	btnc				= ComponentManager->AddComponent<ButtonComponent>(uibtn);
	btnc->SetOwner(uibtn);
	btntf->_size = Vector3(300.0f, 100.0f, 0);
	btnc->AddOnclickFunction(std::bind(&World::EnterCreateState, this));

	EntityManager->GetEntity(uigroup1)->AddChildEntity(uibuttonpannel);
	EntityManager->GetEntity(uigroup1)->AddChildEntity(uimoneypannel);

	EntityManager->GetEntity(uimoneypannel)->SetParentEntity(uigroup1);

	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtn);
	EntityManager->GetEntity(uibuttonpannel)->SetParentEntity(uigroup1);

	EntityManager->GetEntity(uibtn)->SetParentEntity(uibuttonpannel);

	
	
}

World::~World()
{
	UnRegistEvent();
	_mapdata.clear();
	delete _mainCamera;
}

void World::PreUpdate(float dt)
{
}

void World::Update(float dt)
{

}

void World::PostUpdate(float dt)
{
}

void World::OnMapClick(const ClickInGame* event)
{
	if (_actionState == 0) return;
	else {
		if (_actionState == 1) {
			std::pair<int, int> idx = ConvertClickToIdx(Vector3(event->_position.x, event->_position.y, 0));
			if (idx.first > 9 || idx.first < 0 || idx.second > 9 || idx.second < 0) return;
			if (_mapdata[idx.second][idx.first]._tileState == Tile_State::Empty) {
				EntityId newTower = CreateTower(ConvertIdxToTile(idx));
				_mapdata[idx.second][idx.first]._tileState = Tile_State::Tower;
				_mapdata[idx.second][idx.first]._towerGrade = 1;
				_mapdata[idx.second][idx.first]._towerId = newTower;
			}
			_actionState = 0;
		}
	}
}

void World::InitialGame()
{
	std::vector<std::vector<int>> mapdata = ResourceSystem::GetInstance()->LoadMapData();
	for (int i = 0; i < mapdata.size(); i++) {
		std::vector<tileInfo> tmp;
		for (int j = 0; j < mapdata[i].size(); j++) {
			tileInfo info;
			if (mapdata[i][j] == 0) {
				info._tileState = Tile_State::Road;
			}
			else {
				info._tileState = Tile_State::Empty;
			}
			info._towerGrade = 0;
			info._towerId = EntityId();
			tmp.push_back(info);
		}
		_mapdata.push_back(tmp);
	}
}

void World::RegistEvent()
{
	RegisterCallback(&World::OnMapClick);
}

void World::UnRegistEvent()
{
	UnRegisterCallback(&World::OnMapClick);
}

Vector3 World::ConvertIdxToTile(std::pair<int, int>& idx)
{
	return Vector3((idx.first * _sizePerTile + _tileoffset.x), (idx.second * _sizePerTile + _tileoffset.y), 0);
}

std::pair<int, int> World::ConvertClickToIdx(const Vector3& loc)
{
	return std::pair<int, int>((int)((loc.x - _tileoffset.x) / _sizePerTile), (int)((loc.y - _tileoffset.y) / _sizePerTile));
}

EntityId World::CreateTower(const Vector3& loc)
{
	EntityId				tower		= CreateGameObject<Square>(Object_Layer::Player);
	Transform*				tf			= ComponentManager->AddComponent<Transform>(tower, loc, Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*					sp			= ComponentManager->AddComponent<Sprite>(tower, L"Images\\TowerTest");
	BoxCollider*			bc			= ComponentManager->AddComponent<BoxCollider>(tower, sp->_spriteSize);
	DetectComponent*		dc			= ComponentManager->AddComponent<DetectComponent>(tower, 400.0f);
	AttackComponent*		at			= ComponentManager->AddComponent<AttackComponent>(tower, 50, 0.5f);
	tf->SetRectSize(sp->_spriteSize);

	return tower;
}
