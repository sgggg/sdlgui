#include <iostream>
#include <thread>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SGL.h"

#include "CalculatorApp.h"

int CalculatorApp::run()
{
	const auto return_code = initializeSdl();
	if (return_code != 0)
	{
		SDL_Quit();
		return return_code;
	}

	auto sdl_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth_, kScreenHeight_, SDL_WINDOW_SHOWN);
	if (sdl_window == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	calculator_gui_.initialize(kScreenWidth_, kScreenHeight_);

	auto renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

	runUpdateLoop(renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
	return 0;
}

int CalculatorApp::initializeSdl()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (TTF_Init() < 0)
	{
		std::cerr << "SDL_ttf could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	return 0;
}

void CalculatorApp::setUpGui()
{
}

void CalculatorApp::runUpdateLoop(SDL_Renderer* renderer)
{
	auto running = true;
	SDL_Event e;
	std::chrono::system_clock clock;
	const auto maxFps = 30;
	const auto frame_time = std::chrono::microseconds(1'000'000) / maxFps; // e.g. a frame has 1/60 s for 60 fps
	while (running)
	{
		// begin new frame
		auto frame_start = clock.now();

		// 1. advance state of application to the current time
		sgl::SetApplicationTime(std::chrono::duration_cast<std::chrono::milliseconds>(clock.now().time_since_epoch()));

		// 2. handle all input
		while (0 != SDL_PollEvent(&e))
		{
			sgl::HandleEvent(&e);

			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}

		// 3. draw updated state
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		sgl::DrawGui(renderer);
		SDL_RenderPresent(renderer);

		// 4. wait until frame time is over
		auto elapsed = clock.now() - frame_start;
		auto time_left_in_frame = frame_time - elapsed;
		std::this_thread::sleep_for(time_left_in_frame);
	}
}
