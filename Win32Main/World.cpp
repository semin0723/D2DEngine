#include "World.h"
#include "ECSCall.h"
#include "GameObjects.h"
#include "Components.h"

World::World()
{
	RegistEvent();
	_mainCamera = new Camera;

	InitialGame();

	EntityId			bg					= CreateGameObject<Square>(Object_Layer::Background);
	Transform*			tfbg				= ComponentManager->AddComponent<Transform>(bg, Vector3(25.0f, 50.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbg				= ComponentManager->AddComponent<Sprite>(bg, L"Images\\TestBg");
	BoxCollider*		bcbg				= ComponentManager->AddComponent<BoxCollider>(bg, spbg->_spriteSize);
	tfbg->SetRectSize(spbg->_spriteSize);

	{
		// -------- group1 ------------- // main ui
		EntityId			uigroup1		= CreateGameObject<Square>(Object_Layer::UI);
		UITransform*		uitf			= ComponentManager->AddComponent<UITransform>(uigroup1);
		UIGroup*			uig				= ComponentManager->AddComponent<UIGroup>(uigroup1);

		EntityId uibuttonpannel = ButtonArea();
		EntityId uimoneypannel = MoneyArea();
		EntityId uilifepannel = LifeArea();
		EntityId uitimerpannel = TimerArea();

		EntityManager->GetEntity(uigroup1)->AddChildEntity(uibuttonpannel);
		EntityManager->GetEntity(uigroup1)->AddChildEntity(uimoneypannel);
		EntityManager->GetEntity(uigroup1)->AddChildEntity(uilifepannel);
		EntityManager->GetEntity(uigroup1)->AddChildEntity(uitimerpannel);

		EntityManager->GetEntity(uimoneypannel)->SetParentEntity(uigroup1);
		EntityManager->GetEntity(uibuttonpannel)->SetParentEntity(uigroup1);
		EntityManager->GetEntity(uilifepannel)->SetParentEntity(uigroup1);
		EntityManager->GetEntity(uitimerpannel)->SetParentEntity(uigroup1);
	}

	{
		// ------------ group2 ----------------   // pause ui
		EntityId			uigroup2		= CreateGameObject<Square>(Object_Layer::UI);
		UITransform*		ui2tf			= ComponentManager->AddComponent<UITransform>(uigroup2);
		UIGroup*			ui2g			= ComponentManager->AddComponent<UIGroup>(uigroup2);
		_pauseUIGroup = uigroup2;

		EntityId uipausepannel = PauseArea();

		EntityManager->GetEntity(uigroup2)->AddChildEntity(uipausepannel);

		EntityManager->GetEntity(uipausepannel)->SetParentEntity(uigroup2);

		ecs->SendEvent<UIStateChange>(uigroup2, false);
	}
}

World::~World()
{
	UnRegistEvent();
	_mapdata.clear();
	delete _mainCamera;
}

void World::PreUpdate(float dt)
{
	if (_leftTime == 0) return;

	if (_leftTime < 0) {

		ecs->SendEvent<RoundStart>();
		_leftTime = 0;
		return;
	}
	_leftTime -= dt;
}

void World::Update(float dt)
{
	if (_isGameRunning == false) return;

	TextComponent* moneytc = ComponentManager->Getcomponent<TextComponent>(_moneyText);
	moneytc->_text = std::to_wstring(_money);

	TextComponent* lifetc = ComponentManager->Getcomponent<TextComponent>(_lifeText);
	lifetc->_text = std::to_wstring(_life);

	TextComponent* timertc = ComponentManager->Getcomponent<TextComponent>(_timerText);
	timertc->_text = L"00 : " + std::to_wstring((int)_leftTime);
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
				// 자원 부족
				if (_money < 10) return;

				auto [newTower, towerTypeId] = CreateTower(ConvertIdxToTile(idx), 1);
				SetTileInfo(idx, Tile_State::Tower, towerTypeId, newTower, 1);
				_money -= 10;
			}
		}
		else if (_actionState == 2) {
			if (_mapdata[idx.second][idx.first]._tileState == Tile_State::Tower) {
				if (_mapdata[idx.second][idx.first]._towerGrade == 4) return;

				for (int i = 0; i < _mapdata.size(); i++) {
					for (int j = 0; j < _mapdata[i].size(); j++) {
						if (i == idx.second && j == idx.first) continue;
						if (_mapdata[i][j]._tileState != Tile_State::Tower) continue;

						if (
							_mapdata[i][j]._towerGrade == _mapdata[idx.second][idx.first]._towerGrade &&
							_mapdata[i][j]._towerType == _mapdata[idx.second][idx.first]._towerType
							) {
							auto [newTower, towerTypeId] = CreateTower(ConvertIdxToTile(idx), _mapdata[idx.second][idx.first]._towerGrade + 1);
							UINT newGrade = _mapdata[idx.second][idx.first]._towerGrade + 1;
							DeleteTower(idx);
							DeleteTower({ j, i });

							SetTileInfo(idx, Tile_State::Tower, towerTypeId, newTower, newGrade);
							_actionState = 0;
							return;
						}
					}
				}
			}
		}
		else if (_actionState == 3) {
			if (_mapdata[idx.second][idx.first]._tileState == Tile_State::Tower) {
				DeleteTower(idx);
				_money += 50;
			}	
			// 재화 올라가는 이벤트 호출
		}
		_actionState = 0;
	}
}

void World::OnLifeDecrese(const DecreseLife* event)
{
	_life -= event->_life;
	if (_life < 0) _life = 0;
}

void World::OnGetMoney(const GetMoney* event)
{
	_money += event->_earn;
}

void World::OnRoundEnd(const RoundEnd* event)
{
	_leftTime = _waitTime;
}

void World::OnGameOver(const GameOver* event)
{
	Pause();
}

void World::OnGameWin(const GameWin* event)
{
	Pause();
}

void World::InitialGame()
{
	ResourceSystem::GetInstance()->LoadTowerData();
	ResourceSystem::GetInstance()->LoadMonsterData();
	ResourceSystem::GetInstance()->LoadGroundEffect();

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
			info._towerType = 0;
			info._towerGrade = 0;
			info._towerId = EntityId();
			info._groundEffect = EntityId();
			tmp.push_back(info);
		}
		_mapdata.push_back(tmp);
	}
	_leftTime = _waitTime;
}

void World::RegistEvent()
{
	RegisterCallback(&World::OnMapClick);
	RegisterCallback(&World::OnLifeDecrese);
	RegisterCallback(&World::OnGetMoney);
	RegisterCallback(&World::OnRoundEnd);
}

void World::UnRegistEvent()
{
	UnRegisterCallback(&World::OnMapClick);
	UnRegisterCallback(&World::OnLifeDecrese);
	UnRegisterCallback(&World::OnGetMoney);
	UnRegisterCallback(&World::OnRoundEnd);
}

Vector3 World::ConvertIdxToTile(const std::pair<int, int>& idx)
{
	return Vector3((idx.first * _sizePerTile + _tileoffset.x), (idx.second * _sizePerTile + _tileoffset.y), 0);
}

std::pair<int, int> World::ConvertClickToIdx(const Vector3& loc)
{
	return std::pair<int, int>((int)((loc.x - _tileoffset.x) / _sizePerTile), (int)((loc.y - _tileoffset.y) / _sizePerTile));
}

std::pair<EntityId, int> World::CreateTower(const Vector3& loc, UINT towerGrade)
{
	int towerTypeID = GetRandomNum(1, 3);
	TowerInfo newTowerInfo = ResourceSystem::GetInstance()->GetTowerInfo(towerGrade, towerTypeID);
	
	EntityId				tower		= CreateGameObject<Square>(Object_Layer::Player);
	Transform*				tf			= ComponentManager->AddComponent<Transform>(tower, loc, Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*					sp			= ComponentManager->AddComponent<Sprite>(tower, newTowerInfo._imageDirectory);
	BoxCollider*			bc			= ComponentManager->AddComponent<BoxCollider>(tower, Vector3(96.0f, 96.0f, 0));
	DetectComponent*		dc			= ComponentManager->AddComponent<DetectComponent>(tower, newTowerInfo._detectRange);
	AttackComponent*		at			= nullptr;
	if (newTowerInfo._isAreaAttack == false) {
		at = ComponentManager->AddComponent<AttackComponent>(tower, newTowerInfo._towerDamage, newTowerInfo._attackInterval);
	}
	else {
		at = ComponentManager->AddComponent<AttackComponent>(tower, newTowerInfo._towerDamage, newTowerInfo._isAreaAttack, newTowerInfo._attackInterval, newTowerInfo._attackArea);
	}

	sp->_spriteSize = Vector3(96.0f, 96.0f, 0);
	at->_attackEffect = newTowerInfo._effectDirectory;
	tf->SetRectSize(Vector3(96.0f, 96.0f, 0));

	return { tower, towerTypeID };
}

void World::DeleteTower(const std::pair<int, int>& idx)
{
	ecs->SendEvent<GameObjectDestroyed>(_mapdata[idx.second][idx.first]._towerId, Object_Layer::Player);
	EntityManager->DestroyEntity(_mapdata[idx.second][idx.first]._towerId);
	SetTileInfo(idx, Tile_State::Empty, 0, EntityId(), 0);
}

void World::SetTileInfo(const std::pair<int, int>& idx, Tile_State state, UINT towertype, const EntityId& towerId, UINT grade)
{
	
	_mapdata[idx.second][idx.first]._tileState = state;
	_mapdata[idx.second][idx.first]._towerType = towertype;
	_mapdata[idx.second][idx.first]._towerGrade = grade;
	_mapdata[idx.second][idx.first]._towerId = towerId;

	if (grade == 0) {
		ecs->SendEvent<GameObjectDestroyed>(_mapdata[idx.second][idx.first]._groundEffect, Object_Layer::TileEffect);
		_mapdata[idx.second][idx.first]._groundEffect = EntityId();
		return;
	}
	// 바닥 이펙트 생성.
	EntityId			groundEffect	= CreateGameObject<Square>(Object_Layer::TileEffect);
	Transform*			tf				= ComponentManager->AddComponent<Transform>(groundEffect, ConvertIdxToTile(idx) - Vector3(20.0f, 20.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				sp				= ComponentManager->AddComponent<Sprite>(groundEffect, L"Images\\T" + std::to_wstring(grade) + L"_GroundEffect");
	BoxCollider*		bc				= ComponentManager->AddComponent<BoxCollider>(groundEffect, Vector3(96.0f, 96.0f, 0));
	AnimationComponent* ac				= ComponentManager->AddComponent<AnimationComponent>(groundEffect);
	tf->SetRectSize(Vector3(136.0f, 136.0f, 0));
	ac->AddAnimation(L"GroundEffect", ResourceSystem::GetInstance()->GetAnimation(L"GroundEffect"));
	ac->_curAnimationState = L"GroundEffect";

	_mapdata[idx.second][idx.first]._groundEffect = groundEffect;
}

void World::Pause()
{
	ecs->SendEvent<GamePause>();
	ecs->SendEvent<UIStateChange>(_pauseUIGroup, true);
	_isGameRunning ^= true;

}

void World::Resume()
{
	ecs->SendEvent<GamePause>();
	ecs->SendEvent<UIStateChange>(_pauseUIGroup, false);
	_isGameRunning ^= true;
}

void World::Skip()
{
	_leftTime = -1;
}


//------------------------------------------------------------------------------------------------
//----------------------------------------- UI Template ------------------------------------------
//------------------------------------------------------------------------------------------------
EntityId World::MoneyArea()
{
	EntityId			uimoneypannel	= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		pannel2tf		= ComponentManager->AddComponent<UITransform>(uimoneypannel, Vector3(1150.0f, 50.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannel2sp		= ComponentManager->AddComponent<Sprite>(uimoneypannel, L"Images\\UIPannel");
	pannel2tf->_size = Vector3(400.0f, 100.0f, 0);

	EntityId			imagemoney		= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		imguitf			= ComponentManager->AddComponent<UITransform>(imagemoney, Vector3(20.0f, 10.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				imguisp			= ComponentManager->AddComponent<Sprite>(imagemoney, L"Images\\Money");
	imguitf->_size = Vector3(80.0f, 80.0f, 0);

	EntityId			textmoney		= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		textmoneytf		= ComponentManager->AddComponent<UITransform>(textmoney, Vector3(250.0f, 10.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	TextComponent*		textmoneytc		= ComponentManager->AddComponent<TextComponent>(textmoney);
	textmoneytf->_size = Vector3(130.0f, 80.0f, 0);
	textmoneytc->_text = L"0";
	textmoneytc->_fontSize = 40.0f;
	textmoneytc->_textAlignment = DWRITE_TEXT_ALIGNMENT_CENTER;
	textmoneytc->_paragraphAlignemt = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	_moneyText = textmoney;

	EntityManager->GetEntity(uimoneypannel)->AddChildEntity(textmoney);
	EntityManager->GetEntity(uimoneypannel)->AddChildEntity(imagemoney);

	EntityManager->GetEntity(textmoney)->SetParentEntity(uimoneypannel);
	EntityManager->GetEntity(imagemoney)->SetParentEntity(uimoneypannel);

	return uimoneypannel;
}

EntityId World::LifeArea()
{
	EntityId			uilifepannel		= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		pannel2tf			= ComponentManager->AddComponent<UITransform>(uilifepannel, Vector3(1150.0f, 170.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannel2sp			= ComponentManager->AddComponent<Sprite>(uilifepannel, L"Images\\UIPannel");
	pannel2tf->_size = Vector3(400.0f, 100.0f, 0);

	EntityId			imagelife			= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		imguitf				= ComponentManager->AddComponent<UITransform>(imagelife, Vector3(20.0f, 10.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				imguisp				= ComponentManager->AddComponent<Sprite>(imagelife, L"Images\\Life");
	imguitf->_size = Vector3(80.0f, 80.0f, 0);

	EntityId			textlife			= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		textlifetf = ComponentManager->AddComponent<UITransform>(textlife, Vector3(260.0f, 10.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	TextComponent*		textlifetc = ComponentManager->AddComponent<TextComponent>(textlife);
	textlifetf->_size = Vector3(80.0f, 80.0f, 0);
	textlifetc->_text = L"0";
	textlifetc->_fontSize = 40.0f;
	textlifetc->_textAlignment = DWRITE_TEXT_ALIGNMENT_CENTER;
	textlifetc->_paragraphAlignemt = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	_lifeText = textlife;

	EntityManager->GetEntity(uilifepannel)->AddChildEntity(textlife);
	EntityManager->GetEntity(uilifepannel)->AddChildEntity(imagelife);

	EntityManager->GetEntity(textlife)->SetParentEntity(uilifepannel);
	EntityManager->GetEntity(imagelife)->SetParentEntity(uilifepannel);

	return uilifepannel;
}

EntityId World::TimerArea()
{
	EntityId			uitimerpannel		= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		pannel2tf			= ComponentManager->AddComponent<UITransform>(uitimerpannel, Vector3(1150.0f, 290.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannel2sp			= ComponentManager->AddComponent<Sprite>(uitimerpannel, L"Images\\UIPannel");
	pannel2tf->_size = Vector3(400.0f, 100.0f, 0);

	EntityId			imagetimer			= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		timeruitf			= ComponentManager->AddComponent<UITransform>(imagetimer, Vector3(20.0f, 10.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				timeruisp			= ComponentManager->AddComponent<Sprite>(imagetimer, L"Images\\Timer");
	timeruitf->_size = Vector3(80.0f, 80.0f, 0);

	EntityId			texttimer			= EntityManager->CreateEntity<DefaultUIObject>();
	UITransform*		texttimertf			= ComponentManager->AddComponent<UITransform>(texttimer, Vector3(250.0f, 10.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	TextComponent*		texttimertc			= ComponentManager->AddComponent<TextComponent>(texttimer);
	texttimertf->_size = Vector3(130.0f, 80.0f, 0);
	texttimertc->_text = L"0";
	texttimertc->_fontSize = 40.0f;
	texttimertc->_textAlignment = DWRITE_TEXT_ALIGNMENT_CENTER;
	texttimertc->_paragraphAlignemt = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	_timerText = texttimer;

	EntityManager->GetEntity(uitimerpannel)->AddChildEntity(texttimer);
	EntityManager->GetEntity(uitimerpannel)->AddChildEntity(imagetimer);

	EntityManager->GetEntity(texttimer)->SetParentEntity(uitimerpannel);
	EntityManager->GetEntity(imagetimer)->SetParentEntity(uitimerpannel);

	return uitimerpannel;
	
}

EntityId World::ButtonArea()
{
	EntityId			uibuttonpannel		= CreateUIObject<DefaultUIObject>();
	UITransform*		panneltf			= ComponentManager->AddComponent<UITransform>(uibuttonpannel, Vector3(1150.0f, 750.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannelsp			= ComponentManager->AddComponent<Sprite>(uibuttonpannel, L"Images\\UIPannel");
	panneltf->_size = Vector3(400.0f, 400.0f, 0);

	EntityId			uibtnCreateTower	= CreateUIObject<SampleButton>();
	UITransform*		btntf				= ComponentManager->AddComponent<UITransform>(uibtnCreateTower, Vector3(40.0f, 260.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn				= ComponentManager->AddComponent<Sprite>(uibtnCreateTower, L"Images\\Button\\SpawnButtonNormal");
	ButtonComponent*	btnc				= ComponentManager->AddComponent<ButtonComponent>(uibtnCreateTower);
	btnc->SetOwner(uibtnCreateTower);
	btnc->_name = L"Spawn";
	btntf->_size = Vector3(200.0f, 100.0f, 0);
	btnc->AddOnclickFunction(std::bind(&World::EnterCreateState, this));

	EntityId			uibtnDeleteTower	= CreateUIObject<SampleButton>();
	UITransform*		btn2tf				= ComponentManager->AddComponent<UITransform>(uibtnDeleteTower, Vector3(40.0f, 150.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn2				= ComponentManager->AddComponent<Sprite>(uibtnDeleteTower, L"Images\\Button\\DeleteButtonNormal");
	ButtonComponent*	btn2c				= ComponentManager->AddComponent<ButtonComponent>(uibtnDeleteTower);
	btn2c->SetOwner(uibtnDeleteTower);
	btn2c->_name = L"Delete";
	btn2tf->_size = Vector3(200.0f, 100.0f, 0);
	btn2c->AddOnclickFunction(std::bind(&World::EnterDeleteState, this));

	EntityId			uibtnMergeTower		= CreateUIObject<SampleButton>();
	UITransform*		btn3tf				= ComponentManager->AddComponent<UITransform>(uibtnMergeTower, Vector3(40.0f, 40.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn3				= ComponentManager->AddComponent<Sprite>(uibtnMergeTower, L"Images\\Button\\MergeButtonNormal");
	ButtonComponent*	btn3c				= ComponentManager->AddComponent<ButtonComponent>(uibtnMergeTower);
	btn3c->SetOwner(uibtnMergeTower);
	btn3c->_name = L"Merge";
	btn3tf->_size = Vector3(200.0f, 100.0f, 0);
	btn3c->AddOnclickFunction(std::bind(&World::EnterMergeState, this));

	EntityId			uibtnPause			= CreateUIObject<SampleButton>();
	UITransform*		btn4tf				= ComponentManager->AddComponent<UITransform>(uibtnPause, Vector3(270.0f, 260.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn4				= ComponentManager->AddComponent<Sprite>(uibtnPause, L"Images\\Button\\PauseButtonNormal");
	ButtonComponent*	btn4c				= ComponentManager->AddComponent<ButtonComponent>(uibtnPause);
	btn4c->SetOwner(uibtnPause);
	btn4c->_name = L"Pause";
	btn4tf->_size = Vector3(100.0f, 100.0f, 0);
	btn4c->AddOnclickFunction(std::bind(&World::Pause, this));

	EntityId			uibtnSkip			= CreateUIObject<SampleButton>();
	UITransform*		btn5tf				= ComponentManager->AddComponent<UITransform>(uibtnSkip, Vector3(270.0f, 40.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn5				= ComponentManager->AddComponent<Sprite>(uibtnSkip, L"Images\\Button\\SkipButtonNormal");
	ButtonComponent*	btn5c				= ComponentManager->AddComponent<ButtonComponent>(uibtnSkip);
	btn5c->SetOwner(uibtnSkip);
	btn5c->_name = L"Skip";
	btn5tf->_size = Vector3(100.0f, 100.0f, 0);
	btn5c->AddOnclickFunction(std::bind(&World::Skip, this));

	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtnCreateTower);
	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtnDeleteTower);
	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtnMergeTower);
	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtnPause);
	EntityManager->GetEntity(uibuttonpannel)->AddChildEntity(uibtnSkip);

	EntityManager->GetEntity(uibtnCreateTower)->SetParentEntity(uibuttonpannel);
	EntityManager->GetEntity(uibtnDeleteTower)->SetParentEntity(uibuttonpannel);
	EntityManager->GetEntity(uibtnMergeTower)->SetParentEntity(uibuttonpannel);
	EntityManager->GetEntity(uibtnPause)->SetParentEntity(uibuttonpannel);
	EntityManager->GetEntity(uibtnSkip)->SetParentEntity(uibuttonpannel);

	return uibuttonpannel;
}

EntityId World::PauseArea()
{
	EntityId			uipausepannel		= CreateUIObject<DefaultUIObject>();
	UITransform*		panneltf			= ComponentManager->AddComponent<UITransform>(uipausepannel, Vector3(0.0f, 0.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				pannelsp			= ComponentManager->AddComponent<Sprite>(uipausepannel, L"Images\\UIPannel");
	panneltf->_size = Vector3(1600.0f, 1200.0f, 0);
	
	EntityId			uibtnGameResume		= CreateUIObject<SampleButton>();
	UITransform*		btntf				= ComponentManager->AddComponent<UITransform>(uibtnGameResume, Vector3(40.0f, 150.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn				= ComponentManager->AddComponent<Sprite>(uibtnGameResume, L"Images\\Button\\ResumeButtonNormal");
	ButtonComponent*	btnc				= ComponentManager->AddComponent<ButtonComponent>(uibtnGameResume);
	btnc->SetOwner(uibtnGameResume);
	btnc->_name = L"Resume";
	btntf->_size = Vector3(200.0f, 100.0f, 0);
	btnc->AddOnclickFunction(std::bind(&World::Resume, this));

	EntityManager->GetEntity(uipausepannel)->AddChildEntity(uibtnGameResume);

	EntityManager->GetEntity(uibtnGameResume)->SetParentEntity(uipausepannel);

	return uipausepannel;
}



