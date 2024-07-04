#pragma once
#include "resource.h"
#include "framework.h"
#include "D2DRender.h"
#include "TimeSystem.h"

class WinApp {
public:
	WinApp() = default;
	~WinApp() = default;

	virtual void Initialize(HINSTANCE _hInstance);
	void Run();
	virtual void FixedUpdate() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual void Finalize();

	void SetWindowSize(int _width, int _height);
	const D2D1_SIZE_F GetTargetSize() const { return _d2dRender->GetRenderTarget()->GetSize(); }

	ID2D1HwndRenderTarget* GetRenderTarget() const { return _d2dRender->GetRenderTarget(); }

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND _hWnd = { 0 };
	HINSTANCE _hInstance = { 0 };

	D2DRender* _d2dRender = nullptr;
	TimeSystem _time;
	float _timer = 0;

	int _width = 1600;
	int _height = 940;
};