#include <Windows.h>
#include"Window.h"
#include"WindException.h"

//These can be commented out after debugging
#include <string>
#include <sstream>
//Comment out



int APIENTRY wWinMain(
    _In_     HINSTANCE     hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR           lpCmdLine,
    _In_     int                      nCmdShow
)
{
    try 
    {
        //Create a window in the encapsulated Window class
        Window wnd(800, 600, "Retr0 Engine");
        wnd.kbd.EnableAutorepeat();

        //msg handling 
        MSG msg;
        BOOL result;
        //Keep getting messages from window in a loop
        while ((result = GetMessage(&msg, nullptr, 0, 0) > 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            Keyboard::Event e = wnd.kbd.ReadKey();
            if (e.IsHold() && e.GetCode() == VK_MENU) 
            {
                MessageBox(nullptr,"Something Happon!","Space Key Was Pressed",0);
            }
        }
        if (result == -1)
        {
            return -1;
        }

        return (int)msg.wParam;
    }
    catch (const WndException& e) 
    {
        MessageBox(nullptr,e.what(),e.GetType(),MB_OK|MB_ICONEXCLAMATION);
    }
    catch (const std::exception& e)
    {
        MessageBox(nullptr, e.what(), "Std Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBox(nullptr, "No Details Available","Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    return -1;
}




//int CALLBACK WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR		   lpCmdLine,
//	int				   nCmdShow) 
//{
//	return 0;
//}