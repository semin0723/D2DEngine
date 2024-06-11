#pragma once
#include "../D2DEngine/D2DEngine.h"

class DemoApp : public WinApp
{
public:
	DemoApp() = default;
	~DemoApp() = default;

	virtual void Initialize(HINSTANCE _hInstance) override;

	virtual void Update() override;
	virtual void Render(ID2D1HwndRenderTarget* _target) override;

	virtual void Finalize() override;

private:
	ID2D1SolidColorBrush* _blackBrush = { 0 };
	ID2D1SolidColorBrush* _grayBrush = { 0 };
};

