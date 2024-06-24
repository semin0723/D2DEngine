#include "DemoApp.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "InputSystem.h"
#include "PlayerControllSystem.h"
#include "World.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  ȭ���� �����ϴ� ��� �߰�. ���� �ػ� ������ �� ����� �� ���� ��.
	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.
	ECS::Initialize();

	InputSystem* input = ECS::_ecs->GetSystemManager()->AddSystem<InputSystem>();
	PlayerControllSystem* pControll = ECS::_ecs->GetSystemManager()->AddSystem<PlayerControllSystem>();
	RenderSystem* render = ECS::_ecs->GetSystemManager()->AddSystem<RenderSystem>(GetRenderTarget());
	ResourceSystem* resource = ECS::_ecs->GetSystemManager()->AddSystem<ResourceSystem>(GetRenderTarget());
	World* world = ECS::_ecs->GetSystemManager()->AddSystem<World>();

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

	ECS::Finalize();
	__super::Finalize();
}
