#include "Game.h"

Game::Game()
	:
	wnd(800,600,"Retro Engine")
{}

int Game::Start()
{
    //msg handling 
    MSG msg;
    BOOL result;
    //Keep getting messages from window in a loop


    while ((result = GetMessage(&msg, nullptr, 0, 0) > 0))
    {
        // Translate message stuff
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        Update();

        // Do logic
        //Keyboard::Event e = wnd.kbd.ReadKey();
        //Mouse::Event e = wnd.mouse.ReadEvent();
    }

    if (result == -1)
    {
        return -1;
    }

    chronometer = 0.0f;
    return (int)msg.wParam;
}

void Game::Update()
{
    Time::CalculateDelta();
    wnd.kbd.EnableAutorepeat();

    chronometer += Time::delta();

    std::ostringstream oss;
    oss << "Time Elapsed: " << std::setprecision(1) << std::fixed << chronometer;
    wnd.SetTitle(oss.str());
}
