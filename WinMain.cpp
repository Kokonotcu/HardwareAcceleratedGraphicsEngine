#include <Windows.h>
#include"Window.h"
#include"WindException.h"
#include "Game.h"

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
        Game{}.ConstructLoop();
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