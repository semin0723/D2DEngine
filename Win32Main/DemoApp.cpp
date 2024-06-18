#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  ȭ���� �����ϴ� ��� �߰�. ���� �ػ� ������ �� ����� �� ���� ��.
	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.
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
	delete _gameTest;

	ECS::Initialize();
	__super::Finalize();
}
