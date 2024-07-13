#pragma once
#include "Window.h"
#include "Time.h"

class Game
{
public:
	Game();
	int Start();
private:
	void Update();
private:
	Window wnd;
	float chronometer = 0.0f;
};
