#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam, LPARAM Lparam) 
{
    switch (msg)
    {
    case WM_CLOSE :
        PostQuitMessage(1);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, Lparam);
}


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
    wc.lpfnWndProc = WndProc;
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
    //Function to show the window ;D
    ShowWindow(hWnd, SW_SHOW);
    
    //msg handling 
    MSG msg;
    BOOL result;
    while (( result = GetMessage(&msg, nullptr, 0, 0) > 0 )) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if (result == -1) 
    {
        return -1;
    }
    else 
    {
        return msg.wParam;
    }
    
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