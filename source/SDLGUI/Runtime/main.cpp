#include <iostream>
#include <SDL.h>
#include "../SDLGUILIB/SGL.h"


// this currently just shows a blank window for 2 seconds

int main(int /*argc*/, char* /*args*/[])
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 0;
	}

	//Create window
	auto window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	//Get window surface
	auto screenSurface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	sgl::GlobalInitialize();
	auto running = true;
	SDL_Event e;
	while (running)
	{
		while (0 != SDL_PollEvent(&e))
		{
			sgl::HandleEvent(e);
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}
	}
	sgl::GlobalCleanup();

	//Update the surface
	SDL_UpdateWindowSurface(window);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}