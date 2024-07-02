#include "DemoApp.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "InputSystem.h"
#include "PlayerControllSystem.h"
#include "ColliderSystem.h"
#include "World.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  ȭ���� �����ϴ� ��� �߰�. ���� �ػ� ������ �� ����� �� ���� ��.
	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.
	ECS::Initialize();

	InputSystem* input = ECS::_ecs->GetSystemManager()->AddSystem<InputSystem>();
	ResourceSystem::GetInstance()->Initialize(GetRenderTarget());
	RenderSystem* render = ECS::_ecs->GetSystemManager()->AddSystem<RenderSystem>(GetRenderTarget());

	PlayerControllSystem* pControll = ECS::_ecs->GetSystemManager()->AddSystem<PlayerControllSystem>();
	World* world = ECS::_ecs->GetSystemManager()->AddSystem<World>();
	render->SetCurWorld(world);

	ColliderSystem* cs = ECS::_ecs->GetSystemManager()->AddSystem<ColliderSystem>();
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
