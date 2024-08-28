#include "Game.h"

Game::Game()
	:
	wnd(800,600,"Retro Engine")
{}

int Game::ConstructLoop()
{
    Start();
    while (true)
    {
        Time::CalculateDelta();
        if (const auto errcode = Window::ProcessMessage())
        {
            return *errcode;
        }
        Update();
    }
}

void Game::Start() 
{
    wnd.kbd.EnableAutorepeat();
}

//Keyboard::Event e = wnd.kbd.ReadKey();
//Mouse::Event e = wnd.mouse.ReadEvent();
void Game::Update()
{   
    Time::delta();
    const float c = 0.0f;

    wnd.Gfx().ClearBuffer(c, c, 1.0f);
    wnd.Gfx().EndFrame();
}
