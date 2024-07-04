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

	//SetWindowSize(1024, 768);  화면을 변경하는 기능 추가. 추후 해상도 변경할 때 사용할 수 있을 것.
	//TODO: 여기서 코어에 관한 모든 요소를 초기화 합니다.
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
	//TODO:: 여기서 코어에 연결돼있는 모든 요소를 해제해야 합니다.
	ResourceSystem::GetInstance()->DestroyInstance();

	ECS::Finalize();
	__super::Finalize();
}
