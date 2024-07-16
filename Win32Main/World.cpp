#include "World.h"
#include "ECSCall.h"
#include "Square.h"
#include "SampleButton.h"
#include "DefaultUIObject.h"
#include "Components.h"
#include "UITemplate.h"

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

	EntityId			uibtn				= CreateUIObject<SampleButton>();
	UITransform*		btntf				= ComponentManager->AddComponent<UITransform>(uibtn, Vector3(50.0f, 250.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn				= ComponentManager->AddComponent<Sprite>(uibtn, L"Images\\Button\\ButtonNormal");
	ButtonComponent*	btnc				= ComponentManager->AddComponent<ButtonComponent>(uibtn);
	btnc->SetOwner(uibtn);
	btntf->_size = Vector3(300.0f, 100.0f, 0);
	btnc->AddOnclickFunction(std::bind(&World::EnterCreateState, this));

	EntityId			uibtn2				= CreateUIObject<SampleButton>();
	UITransform*		btn2tf				= ComponentManager->AddComponent<UITransform>(uibtn2, Vector3(50.0f, 140.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn2				= ComponentManager->AddComponent<Sprite>(uibtn2, L"Images\\Button\\ButtonNormal");
	ButtonComponent*	btn2c				= ComponentManager->AddComponent<ButtonComponent>(uibtn2);
	btn2c->SetOwner(uibtn2);
	btn2tf->_size = Vector3(300.0f, 100.0f, 0);
	btn2c->AddOnclickFunction(std::bind(&World::EnterDeleteState, this));

	EntityId			uibtn3				= CreateUIObject<SampleButton>();
	UITransform*		btn3tf				= ComponentManager->AddComponent<UITransform>(uibtn3, Vector3(50.0f, 30.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn3				= ComponentManager->AddComponent<Sprite>(uibtn3, L"Images\\Button\\ButtonNormal");
	ButtonComponent*	btn3c				= ComponentManager->AddComponent<ButtonComponent>(uibtn3);
	btn3c->SetOwner(uibtn3);
	btn3tf->_size = Vector3(300.0f, 100.0f, 0);
	btn3c->AddOnclickFunction(std::bind(&World::EnterMergeState, this));

	EntityId uimoneypannel = MoneyArea();

	EntityManager->GetEntity(uigroup1)->AddChildEntity(uibuttonpannel);
	EntityManager->GetEntity(uigroup1)->AddChildEntity(uimoneypannel);

	EntityManager->GetEntity(uimoneypannel)->SetParentEntity(uigroup1);

	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtn);
	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtn2);
	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtn3);
	EntityManager->GetEntity(uibuttonpannel)->SetParentEntity(uigroup1);

	EntityManager->GetEntity(uibtn)->SetParentEntity(uibuttonpannel);
	EntityManager->GetEntity(uibtn2)->SetParentEntity(uibuttonpannel);
	EntityManager->GetEntity(uibtn3)->SetParentEntity(uibuttonpannel);

	
	
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
	TextComponent* lifetc = ComponentManager->Getcomponent<TextComponent>(_lifeText);
	lifetc->_text = std::to_wstring(_life);
}

void World::PostUpdate(float dt)
{
}

void World::OnMapClick(const ClickInGame* event)
{
	if (_actionState == 0) return;
	else {
		std::pair<int, int> idx = ConvertClickToIdx(Vector3(event->_position.x, event->_position.y, 0));
		if (idx.first > 9 || idx.first < 0 || idx.second > 9 || idx.second < 0) {
			_actionState = 0;
			return;
		}
		
		if (_actionState == 1) {
			if (_mapdata[idx.second][idx.first]._tileState == Tile_State::Empty) {
				EntityId newTower = CreateTower(ConvertIdxToTile(idx), 1);
				SetTileInfo(idx, Tile_State::Tower, Tower_Type::Tower1_1, newTower, 1);
			}
		}
		else if (_actionState == 2) {
			if (_mapdata[idx.second][idx.first]._tileState == Tile_State::Tower) {
				for (int i = 0; i < _mapdata.size(); i++) {
					for (int j = 0; j < _mapdata[i].size(); j++) {
						if (i == idx.second && j == idx.first) continue;
						if (_mapdata[i][j]._tileState != Tile_State::Tower) continue;

						if (
							_mapdata[i][j]._towerGrade == _mapdata[idx.second][idx.first]._towerGrade &&
							_mapdata[i][j]._towerType == _mapdata[idx.second][idx.first]._towerType
							) {
							EntityId newTower = CreateTower(ConvertIdxToTile(idx), _mapdata[idx.second][idx.first]._towerGrade);
							UINT newGrade = _mapdata[idx.second][idx.first]._towerGrade + 1;
							DeleteTower(idx);
							DeleteTower({ j, i });

							SetTileInfo(idx, Tile_State::Tower, Tower_Type::Tower1_2, newTower, newGrade);
						}
					}
				}
			}
		}
		else if (_actionState == 3) {
			if (_mapdata[idx.second][idx.first]._tileState == Tile_State::Tower) {
				DeleteTower(idx);
			}	
			// 재화 올라가는 이벤트 호출
		}
		_actionState = 0;
	}
}

void World::OnLifeDecrese(const DecreseLife* event)
{
	_life -= event->_life;
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
			info._towerType = Tower_Type::Default;
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
	RegisterCallback(&World::OnLifeDecrese);
}

void World::UnRegistEvent()
{
	UnRegisterCallback(&World::OnMapClick);
	UnRegisterCallback(&World::OnLifeDecrese);
}

Vector3 World::ConvertIdxToTile(std::pair<int, int>& idx)
{
	return Vector3((idx.first * _sizePerTile + _tileoffset.x), (idx.second * _sizePerTile + _tileoffset.y), 0);
}

std::pair<int, int> World::ConvertClickToIdx(const Vector3& loc)
{
	return std::pair<int, int>((int)((loc.x - _tileoffset.x) / _sizePerTile), (int)((loc.y - _tileoffset.y) / _sizePerTile));
}

EntityId World::CreateTower(const Vector3& loc, UINT towerGrade)
{
	EntityId				tower		= CreateGameObject<Square>(Object_Layer::Player);
	Transform*				tf			= ComponentManager->AddComponent<Transform>(tower, loc, Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*					sp			= ComponentManager->AddComponent<Sprite>(tower, L"Images\\TowerTest");
	BoxCollider*			bc			= ComponentManager->AddComponent<BoxCollider>(tower, sp->_spriteSize);
	DetectComponent*		dc			= ComponentManager->AddComponent<DetectComponent>(tower, 200.0f);
	AttackComponent*		at			= ComponentManager->AddComponent<AttackComponent>(tower, 50, 0.5f);
	tf->SetRectSize(sp->_spriteSize);

	return tower;
}

void World::DeleteTower(const std::pair<int, int>& idx)
{
	ecs->SendEvent<GameObjectDestroyed>(_mapdata[idx.second][idx.first]._towerId, Object_Layer::Player);
	SetTileInfo(idx, Tile_State::Empty, Tower_Type::Default, EntityId(), 0);
}

void World::SetTileInfo(const std::pair<int, int>& idx, Tile_State state, Tower_Type type, const EntityId& towerId, UINT grade)
{
	_mapdata[idx.second][idx.first]._tileState = state;
	_mapdata[idx.second][idx.first]._towerType = type;
	_mapdata[idx.second][idx.first]._towerGrade = grade;
	_mapdata[idx.second][idx.first]._towerId = towerId;
}

EntityId World::MoneyArea()
{
	EntityId			uimoneypannel	= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		pannel2tf		= ComponentManager->AddComponent<UITransform>(uimoneypannel, Vector3(1150.0f, 50.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannel2sp		= ComponentManager->AddComponent<Sprite>(uimoneypannel, L"Images\\UIPannel");
	pannel2tf->_size = Vector3(400.0f, 100.0f, 0);

	EntityId			textmoney		= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		textmoneytf		= ComponentManager->AddComponent<UITransform>(textmoney, Vector3(300.0f, 10.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	TextComponent*		textmoneytc		= ComponentManager->AddComponent<TextComponent>(textmoney);
	textmoneytf->_size = Vector3(80.0f, 80.0f, 0);
	textmoneytc->_text = L"0";
	textmoneytc->_fontSize = 50.0f;
	textmoneytc->_textAlignment = DWRITE_TEXT_ALIGNMENT_CENTER;
	textmoneytc->_paragraphAlignemt = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	_lifeText = textmoney;

	EntityManager->GetEntity(uimoneypannel)->AddChildEntity(textmoney);
	EntityManager->GetEntity(textmoney)->SetParentEntity(uimoneypannel);

	return uimoneypannel;
}

