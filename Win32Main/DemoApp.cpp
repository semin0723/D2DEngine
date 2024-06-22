#include "DemoApp.h"
#include "RenderSystem.h"
#include "World.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  ȭ���� �����ϴ� ��� �߰�. ���� �ػ� ������ �� ����� �� ���� ��.
	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.
	ECS::Initialize();

	RenderSystem* render = ECS::_ecs->GetSystemManager()->AddSystem<RenderSystem>(GetRenderTarget());
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
