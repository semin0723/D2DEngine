#include "DemoApp.h"
#include "RenderSystem.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  화면을 변경하는 기능 추가. 추후 해상도 변경할 때 사용할 수 있을 것.
	//TODO: 여기서 코어에 관한 모든 요소를 초기화 합니다.
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
	//TODO:: 여기서 코어에 연결돼있는 모든 요소를 해제해야 합니다.

	ECS::Finalize();
	__super::Finalize();
}
