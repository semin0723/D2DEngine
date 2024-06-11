#include "D2DEngine.h"

void WinApp::Initialize(HINSTANCE _hInstance) {

    WNDCLASS wcex;

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    wcex.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_D2DENGINE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"Template";

    RegisterClass(&wcex);

    RECT winRect = { 0, 0, _width, _height };
    ::AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);

    _hWnd = CreateWindowW(L"Template", L"Template", WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, 0, _width, _height, nullptr, nullptr, _hInstance, nullptr);

    ShowWindow(_hWnd, SW_SHOWNORMAL);
    UpdateWindow(_hWnd);

    _d2dRender = new D2DRender;
    _d2dRender->Initialize(_hWnd);
}

void WinApp::Run()
{
    MSG msg;

    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            else {
                DispatchMessage(&msg);
            }
        }
        else {
            _d2dRender->GetRenderTarget()->BeginDraw();
            _d2dRender->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));

            Update();
            Render(_d2dRender->GetRenderTarget());

            _d2dRender->GetRenderTarget()->EndDraw();
        }
    }
}

void WinApp::Finalize()
{
    _d2dRender->Finalize();
    delete _d2dRender;
}

LRESULT CALLBACK WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}