#pragma once

#include "SDL.h"
#include "CalculatorGui.h"

class CalculatorApp
{
public:
	int run();

private:
	const int kScreenWidth_ = 350;
	const int kScreenHeight_ = 400;

	CalculatorGui calculator_gui_;

	int initializeSdl();
	void setUpGui();
	void runUpdateLoop(SDL_Renderer* renderer);
};
