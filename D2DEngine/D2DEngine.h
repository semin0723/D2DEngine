#pragma once
#include "resource.h"
#include "framework.h"
#include "D2DRender.h"

class WinApp {
public:
	WinApp() = default;
	~WinApp() = default;

	virtual void Initialize(HINSTANCE _hInstance);
	void Run();
	virtual void Update() {}
	virtual void Render(ID2D1HwndRenderTarget* _target) {}
	virtual void Finalize();

	void SetWindowSize(int _width, int _height);

	ID2D1HwndRenderTarget* GetRenderTarget() const { return _d2dRender->GetRenderTarget(); }

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND _hWnd = { 0 };
	HINSTANCE _hInstance = { 0 };

	D2DRender* _d2dRender = nullptr;

	int _width = 800;
	int _height = 600;
};