#include "DemoApp.h"
#include "RenderSystem.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  ȭ���� �����ϴ� ��� �߰�. ���� �ػ� ������ �� ����� �� ���� ��.
	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.
	ECS::Initialize();
	RenderSystem* render = ECS::_ecs->GetSystemManager()->AddSystem<RenderSystem>(GetRenderTarget());
	EntityId eid = ECS::_ecs->GetEntityManager()->CreateEntity<Box>();
	IEntity* entity = ECS::_ecs->GetEntityManager()->GetEntity(eid);
	ECS::_ecs->SendEvent<GameObjectCreated>(entity->GetEntityId(), entity->GetEntityTypeId());
	ECS::_ecs->GetComponentManager()->AddComponent<BoxComponent>(eid, 100.0f, 100.0f, 200.0f, 200.0f);
}

void DemoApp::Update(float dt)
{
	//ECS::_ecs->SendEvent<DrawRectangle>(200.0f, 200.0f, 500.0f, 600.0f);
	ECS::_ecs->Update(dt);
}

void DemoApp::Render()
{
	// ������ ����� ���Ŀ� �̺�Ʈ �ý��ۿ��� ó���ϴ� ������ ������ �õ��غ� �����Դϴ�.
	//for (float y = 0; y < GetTargetSize().height; y += 10)
	//{
	//	_renderComponent.DrawLine(0, y, GetTargetSize().width, y, BLACK, 0.5f);
	//}

	//_renderComponent.DrawFillRectangle(300.0f, 300.0f, 500.0f, 600.0f, GRAY);

	//_renderComponent.DrawRectangle(10.0f, 10.0f, 100.0f, 100.0f, BLACK);
}

void DemoApp::Finalize()
{
	//TODO:: ���⼭ �ھ ������ִ� ��� ��Ҹ� �����ؾ� �մϴ�.
	_renderComponent.Finalize();

	ECS::Initialize();
	__super::Finalize();
}
