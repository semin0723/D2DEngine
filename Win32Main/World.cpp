#include "World.h"
#include "ECSCall.h"
#include "Square.h"
#include "SampleButton.h"
#include "Components.h"

World::World()
{
	_mainCamera = new Camera;

	EntityId			square		= CreateGameObject<Square>(Object_Layer::Player);
	Transform*			tf			= ComponentManager->AddComponent<Transform>(square, Vector3(200.0f, 100.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				sp			= ComponentManager->AddComponent<Sprite>(square, L"Images\\TowerTest");
	BoxCollider*		bc			= ComponentManager->AddComponent<BoxCollider>(square, sp->_spriteSize);
	DetectComponent*	dc			= ComponentManager->AddComponent<DetectComponent>(square, 400.0f);
	AttackComponent*	at			= ComponentManager->AddComponent<AttackComponent>(square, 50, 0.5f);
	tf->SetRectSize(sp->_spriteSize);
	ecs->SendEvent<RegistPlayer>(square);

	EntityId			bg			= CreateGameObject<Square>(Object_Layer::Background);
	Transform*			tfbg		= ComponentManager->AddComponent<Transform>(bg, Vector3(350.0f, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbg		= ComponentManager->AddComponent<Sprite>(bg, L"Images\\TestBg");
	BoxCollider*		bcbg		= ComponentManager->AddComponent<BoxCollider>(bg, spbg->_spriteSize);
	tfbg->SetRectSize(spbg->_spriteSize);

	EntityId			uigroup1	= CreateGameObject<Square>(Object_Layer::UI);
	UITransform*		uitf		= ComponentManager->AddComponent<UITransform>(uigroup1);
	UIGroup*			uig			= ComponentManager->AddComponent<UIGroup>(uigroup1);
	
	EntityId			uibtn		= CreateUIObject<SampleButton>();
	UITransform*		btntf		= ComponentManager->AddComponent<UITransform>(uibtn, Vector3(100.0f, 500.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				spbtn		= ComponentManager->AddComponent<Sprite>(uibtn, L"Images\\Button\\ButtonNormal");
	ButtonComponent*	btnc		= ComponentManager->AddComponent<ButtonComponent>(uibtn);
	btnc->SetOwner(uibtn);
	btntf->_size = spbtn->_spriteSize;
	btnc->AddOnclickFunction(std::bind(&World::MoveCamera, this));

	EntityManager->GetEntity(uigroup1)->AddChildEntity(uibtn);
	EntityManager->GetEntity(uibtn)->SetParentEntity(uigroup1);

}

World::~World()
{
	for (int i = 0; i < _objects.size(); i++) {
		EntityManager->DestroyEntity(_objects[i]);
	}
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

void World::MoveCamera()
{
	EntityId			square		= CreateGameObject<Square>(Object_Layer::Player);
	Transform*			tf			= ComponentManager->AddComponent<Transform>(square, Vector3(500.0f, 100.0f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0, 0, 0));
	Sprite*				sp			= ComponentManager->AddComponent<Sprite>(square, L"Images\\TowerTest");
	BoxCollider*		bc			= ComponentManager->AddComponent<BoxCollider>(square, sp->_spriteSize);
	DetectComponent*	dc			= ComponentManager->AddComponent<DetectComponent>(square, 400.0f);
	AttackComponent*	at			= ComponentManager->AddComponent<AttackComponent>(square, 50, 0.5f);
	tf->SetRectSize(sp->_spriteSize);
}

void World::RegistEvent()
{
}

void World::UnRegistEvent()
{
}
