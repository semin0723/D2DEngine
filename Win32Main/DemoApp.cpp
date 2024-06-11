#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//TODO: 여기서 코어에 관한 모든 요소를 초기화 합니다.
}

void DemoApp::Update()
{
}

void DemoApp::Render(ID2D1HwndRenderTarget* _target)
{
}

void DemoApp::Finalize()
{
	//TODO:: 여기서 코어에 연결돼있는 모든 요소를 해제해야 합니다.

	__super::Finalize();
}
