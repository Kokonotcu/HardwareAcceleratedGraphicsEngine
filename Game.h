#pragma once
#include "Window.h"
#include "Time.h"

class Game
{
public:
	Game();
	int ConstructLoop();
private:
	void Update();
	void Start();
private:
	Window wnd;
};
