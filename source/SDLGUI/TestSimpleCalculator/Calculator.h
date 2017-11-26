#pragma once

#include "SDL.h"

enum class Operation
{
	EnterDigit0 = 0,
	EnterDigit1 = 1,
	EnterDigit2 = 2,
	EnterDigit3 = 3,
	EnterDigit4 = 4,
	EnterDigit5 = 5,
	EnterDigit6 = 6,
	EnterDigit7 = 7,
	EnterDigit8 = 8,
	EnterDigit9 = 9,
	Add,
	Subtract,
	Multiply,
	Divide,
	Negate,
	CalculateResult,
	SetDecimalPoint,
	Clear,
};

class CalculatorApp
{
public:
	int run();

	void doOperation(Operation operation);

private:
	const int kScreenWidth_ = 350;
	const int kScreenHeight_ = 400;

	int initializeSdl();
	void runUpdateLoop(SDL_Renderer* renderer);
};
