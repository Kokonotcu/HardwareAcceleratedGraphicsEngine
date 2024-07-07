#include "Window.h"
#include "Windowsx.h"
#include <sstream>
#include "resource.h"

Window::WindowClass Window::WindowClass::wndClass;

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
    :
    WndException(line , file),
    hr(hr)
{
}

const char* Window::Exception::what()const noexcept
{
    std::stringstream ss;
    ss << GetType() << std::endl
        << "[Error Code]" << GetErrorCode() << std::endl
        << "[Description]" << GetErrorString() << std::endl
        << GetOriginString();
    return ss.str().c_str();
}

const char* Window::Exception::GetType() const noexcept 
{
    return "Wnd Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
    char* pMsgBuf = nullptr;
    DWORD nMsgLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER|
        FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,hr,MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&pMsgBuf),0,nullptr
        );
    if (nMsgLen == 0)
    {
        return "Unidentified error code";
    }
    std::string errorString = pMsgBuf;
    LocalFree(pMsgBuf);
    return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
    return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
    return TranslateErrorCode(hr);
}

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
    wc.hIcon = static_cast<HICON>( LoadImage(hInst,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,48,48,0));
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = GetName();
    wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));;
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


Window::Window(int width, int height, const char* name)
    :
    width(width),
    height(height)
{
    
    RECT wr;
    wr.left = 100;
    wr.right = wr.left + width;
    wr.top = 100;
    wr.bottom = wr.top + height; 
    if ( AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
    {
        throw WND_LAST_EXCEPT();
    }
    
    //Initialize Window instance
    hWnd = CreateWindow(WindowClass::GetName(), name,
        WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU,
        CW_USEDEFAULT,CW_USEDEFAULT,wr.right - wr.left,wr.bottom - wr.top,nullptr,nullptr,
        WindowClass::GetInstance(),this
        );
    if (hWnd == nullptr)
    {
        throw WND_LAST_EXCEPT();
    }
    //Function to show the window ;D
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

void Window::SetTitle(const std::string& title) 
{
    if (SetWindowText( hWnd , title.c_str()) == 0 ) 
    {
        throw WND_LAST_EXCEPT();
    }
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
            //Clear keystate when lost focus
        case WM_KILLFOCUS:
            kbd.ClearState();
            break;
         /****************  KEYBOARD MESSAGES  **************************/
        case WM_KEYDOWN:
        //Also handle sytem keys like ALT or F10
        case WM_SYSKEYDOWN:
            kbd.OnKeyPressed(static_cast<unsigned char>(wParam), lParam);
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:
            kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
            break;
        case WM_CHAR:
            kbd.OnChar(static_cast<unsigned char>(wParam));
            break;
        /****************  END KEYBOARD MESSAGES  **************************/

        /****************  MOUSE MESSAGES  **************************/
        case WM_MOUSEMOVE: 
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnMouseMove(pt.x, pt.y);

            //In client region
            if (pt.x >= 0 &&  pt.x < width && pt.y >= 0 && pt.y < height)
            {
                if (!mouse.IsInWindow())
                {
                    SetCapture(hWnd);
                    mouse.OnMouseEnter();
                }
            }
            //Outside client region
            else 
            {
                if (!(mouse.leftIsPressed || mouse.rightIsPressed || mouse.middleIsPressed))
                {
                    ReleaseCapture();
                    mouse.OnMouseLeave();
                }
            }
        }
            break;
        case WM_LBUTTONDOWN:
            mouse.OnLeftPressed();
            break;
        case WM_LBUTTONUP:
            mouse.OnLeftReleased();
            break;
        case WM_RBUTTONDOWN:
            mouse.OnRightPressed();
            break;
        case WM_RBUTTONUP:
            mouse.OnRightReleased();
            break;
        case WM_MBUTTONDOWN:
            mouse.OnMiddlePressed();
            break;
        case WM_MBUTTONUP:
            mouse.OnMiddleReleased();
            break;
        case WM_MOUSEWHEEL:
            if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) 
            {
                mouse.WheelUp();
            }
            else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) 
            {
                mouse.WheelDown(); 
            }
            break;
            
        /****************  END MOUSE MESSAGES  **************************/

    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
