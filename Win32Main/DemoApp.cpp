#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//SetWindowSize(1024, 768);  화면을 변경하는 기능 추가. 추후 해상도 변경할 때 사용할 수 있을 것.
	//TODO: 여기서 코어에 관한 모든 요소를 초기화 합니다.
	// RenderComponent->Initialize(GetRenderTarget());
}

void DemoApp::Update()
{
}

void DemoApp::Render(ID2D1HwndRenderTarget* _target)
{
	//TODO: 지금은 임시로 넣어뒀지만, brush를 생성하는 과정을 initialize 때 랜더링하는 기능을 따로 분리해서 추가해야합니다.
	if (_blackBrush == nullptr) {
		_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &_blackBrush);
	}
	if (_grayBrush == nullptr) {
		_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &_grayBrush);
	}

	D2D1_SIZE_F size = _target->GetSize();
	for (float y = 0; y < size.height; y += 10)
	{
		_target->DrawLine(
			D2D1::Point2F(0.0f, y),
			D2D1::Point2F(size.width, y),
			_blackBrush, 0.5f

		);
	}

	_target->FillRectangle(
		D2D1::RectF(size.width / 2 - 150.0f, size.height / 2 - 150.0f,
			size.width / 2 + 150.0f, size.height / 2 + 150.0f), _grayBrush
	);

	_target->DrawRectangle(
		D2D1::RectF(size.width / 2 - 50.0f, size.height / 2 - 50.0f,
			size.width / 2 + 50.0f, size.height / 2 + 50.0f), _blackBrush
	);
}

void DemoApp::Finalize()
{
	//TODO:: 여기서 코어에 연결돼있는 모든 요소를 해제해야 합니다.
	if (_blackBrush) _blackBrush->Release();
	if (_grayBrush) _grayBrush->Release();

	__super::Finalize();
}
