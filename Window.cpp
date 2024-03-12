#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;


Window::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
    //Register Windows Class
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMsgStart;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetInstance();
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = GetName();
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass() 
{
    UnregisterClass(GetName(), GetInstance());
}

const char* Window::WindowClass::GetName() noexcept 
{
    return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept 
{
    return wndClass.hInst;
}




Window::Window(int width, int height, const char* name) noexcept
    :
    width(width),
    height(height)
{
    
    RECT wr;
    wr.left = 100;
    wr.right = wr.left + width;
    wr.top = 100;
    wr.bottom = wr.top + height;   
    AdjustWindowRect(&wr,WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,FALSE);
    //Initialize Window instance
    hWnd = CreateWindow(WindowClass::GetName(), name,
        WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
        CW_USEDEFAULT,CW_USEDEFAULT,wr.right - wr.left,wr.bottom - wr.top,nullptr,nullptr,
        WindowClass::GetInstance(),this
        );
    //hWnd = CreateWindowEx(0,
    //    WindowClass::GetName(),name,
    //    WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
    //    wr.right - wr.left, wr.bottom - wr.top,nullptr,nullptr, WindowClass::GetInstance(),
    //    this
    //    );

    //Function to show the window ;D
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

LRESULT Window::HandleMsgStart(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
    if (msg == WM_NCCREATE)
    {
        // extract ptr to window class from creation data
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
        // set WinAPI-managed user data to store ptr to window instance
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        // set message proc to normal (non-setup) handler now that setup is finished
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgUpdate));
        // forward message to window instance handler
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    // if we get a message before the WM_NCCREATE message, handle with default handler
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgUpdate(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // retrieve ptr to window instance
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    // forward message to window instance handler
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
        // we don't want the DefProc to handle this message because
        // we want our destructor to destroy the window, so return 0 instead of break
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
