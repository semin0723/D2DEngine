#include "DemoApp.h"

void DemoApp::Initialize(HINSTANCE _hInstance)
{
	__super::Initialize(_hInstance);

	//TODO: ���⼭ �ھ ���� ��� ��Ҹ� �ʱ�ȭ �մϴ�.

}

void DemoApp::Update()
{
}

void DemoApp::Render(ID2D1HwndRenderTarget* _target)
{
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
	//TODO:: ���⼭ �ھ ������ִ� ��� ��Ҹ� �����ؾ� �մϴ�.
	if (_blackBrush) _blackBrush->Release();
	if (_grayBrush) _grayBrush->Release();

	__super::Finalize();
}
