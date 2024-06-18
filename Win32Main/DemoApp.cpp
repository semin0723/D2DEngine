#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  화면을 변경하는 기능 추가. 추후 해상도 변경할 때 사용할 수 있을 것.
	//TODO: 여기서 코어에 관한 모든 요소를 초기화 합니다.
	ECS::Initialize();
	_renderComponent.Initialize(GetRenderTarget());
	_gameTest = new Test;
	_gameTest->_render = &_renderComponent;
}

void DemoApp::Update()
{
	ECS::_ecs->SendEvent<DrawRectangle>(300.0f, 300.0f, 500.0f, 600.0f);
	ECS::_ecs->Update();
}

void DemoApp::Render()
{
	// 랜더링 기능을 추후에 이벤트 시스템에서 처리하는 식으로 변경을 시도해볼 예정입니다.
	//for (float y = 0; y < GetTargetSize().height; y += 10)
	//{
	//	_renderComponent.DrawLine(0, y, GetTargetSize().width, y, BLACK, 0.5f);
	//}

	//_renderComponent.DrawFillRectangle(300.0f, 300.0f, 500.0f, 600.0f, GRAY);

	//_renderComponent.DrawRectangle(10.0f, 10.0f, 100.0f, 100.0f, BLACK);
}

void DemoApp::Finalize()
{
	//TODO:: 여기서 코어에 연결돼있는 모든 요소를 해제해야 합니다.
	_renderComponent.Finalize();
	delete _gameTest;

	ECS::Initialize();
	__super::Finalize();
}
