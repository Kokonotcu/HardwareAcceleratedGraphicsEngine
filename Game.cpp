#include "Game.h"

Game::Game()
	:
	wnd(800,600,"Retr0 Engine")
{}

int Game::ConstructLoop()
{
    Start();
    wnd.mouse.Clear();
    while (true)
    {
        Time::CalculateDelta();
        if (const auto errcode = Window::ProcessMessage())
        {
            return *errcode;
        }
        wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);
        Update();
        wnd.Gfx().EndFrame();
    }
}

void Game::Start() 
{
    wnd.kbd.EnableAutorepeat();
}

//Time::delta();
//Keyboard::Event e = wnd.kbd.ReadKey();
//Mouse::Event e = wnd.mouse.ReadEvent();
//wnd.Gfx().ClearBuffer(1.0f, 1.0f, 1.0f);
void Game::Update()
{   
    chronometer += Time::delta();
    wnd.Gfx().DrawTestTriangle(
        chronometer,
        0.0f,
        0.0f
    );
    wnd.Gfx().DrawTestTriangle(
        -chronometer,
        wnd.mouse.GetPos().first / 400.0f - 1.0f,
        -wnd.mouse.GetPos().second / 300.0f + 1.0f
    );
}
