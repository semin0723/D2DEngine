#include "DemoApp.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "InputSystem.h"
#include "PlayerControllSystem.h"
#include "ColliderSystem.h"
#include "MonsterControll.h"
#include "World.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  ȭ���� �����ϴ� ��� �߰�. ���� �ػ� ������ �� ����� �� ���� ��.
	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.
	ECS::Initialize();

	InputSystem* input = SystemManager->AddSystem<InputSystem>();
	ResourceSystem::GetInstance()->Initialize(GetRenderTarget());
	RenderSystem* render = SystemManager->AddSystem<RenderSystem>(GetRenderTarget());

	PlayerControllSystem* pControll = SystemManager->AddSystem<PlayerControllSystem>();
	MonsterControll* mctrl = SystemManager->AddSystem<MonsterControll>();
	World* world = SystemManager->AddSystem<World>();
	render->SetCurWorld(world);

	ColliderSystem* cs = SystemManager->AddSystem<ColliderSystem>();
	cs->SetCollisionMatrix(Object_Layer::Player, Object_Layer::Monster);


}

void DemoApp::Update(float dt)
{
	ECS::_ecs->Update(dt);
}

void DemoApp::Render()
{

}

void DemoApp::Finalize()
{
	//TODO:: ���⼭ �ھ ������ִ� ��� ��Ҹ� �����ؾ� �մϴ�.
	ResourceSystem::GetInstance()->DestroyInstance();

	ECS::Finalize();
	__super::Finalize();
}
