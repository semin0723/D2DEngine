#include "Windows.h"
#include "DemoApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    DemoApp winApp;

    winApp.Initialize(hInstance);
    winApp.Run();
    winApp.Finalize();

    return EXIT_SUCCESS;
}