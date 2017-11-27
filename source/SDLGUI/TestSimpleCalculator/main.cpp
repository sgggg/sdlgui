#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#undef WIN32_LEAN_AND_MEAN

#include "CalculatorApp.h"

int CALLBACK WinMain(
	_In_ HINSTANCE /*hInstance*/,
	_In_ HINSTANCE /*hPrevInstance*/,
	_In_ LPSTR     /*lpCmdLine*/,
	_In_ int       /*nCmdShow*/)
{
	CalculatorApp calc;
	return calc.run();
}
