#include <Windows.h>


int APIENTRY wWinMain(
    _In_     HINSTANCE     hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR           lpCmdLine,
    _In_     int                      nCmdShow
)
{
    //Register Windows Class
    const LPCWSTR className = L"render3d";
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = DefWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszClassName = className;
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);
    //Initialize Window instance
    HWND hWnd = CreateWindowEx
    (0, className,
        L"3DRenderEngine",
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU , 
        200, 200 , 640 , 480,
        nullptr, nullptr, hInstance, nullptr
    );
    ShowWindow(hWnd, SW_SHOW);
    while (true);
    
    return 0;
}




//int CALLBACK WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR		   lpCmdLine,
//	int				   nCmdShow) 
//{
//	return 0;
//}