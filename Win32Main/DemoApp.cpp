#include "DemoApp.h"
#include "RenderSystem.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  ȭ���� �����ϴ� ��� �߰�. ���� �ػ� ������ �� ����� �� ���� ��.
	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.
	ECS::Initialize();
	RenderSystem* render = ECS::_ecs->GetSystemManager()->AddSystem<RenderSystem>(GetRenderTarget());
	//EntityId eid = ECS::_ecs->GetEntityManager()->CreateEntity<Box>();
	//IEntity* entity = ECS::_ecs->GetEntityManager()->GetEntity(eid);
	//ECS::_ecs->SendEvent<GameObjectCreated>(entity->GetEntityId(), entity->GetEntityTypeId());
	//ECS::_ecs->GetComponentManager()->AddComponent<BoxComponent>(eid, 100.0f, 100.0f, 200.0f, 200.0f);
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
