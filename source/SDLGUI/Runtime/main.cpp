#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "../SDLGUILIB/SGL.h"


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

	if (TTF_Init() < 0)
	{
		std::cerr << "SDL_ttf could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 0;
	}

	//Create window
	auto sdlWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (sdlWindow == nullptr)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	// get 2D rendering context
	auto renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	
	// create GUI
	sgl::Gui gui;

	// create new window
	sgl::Window w(&gui, "Main Window");
	w.setSize(400, 300);

	// add button to window
	sgl::Button b(&w, "Press Me!");
	b.setPosition(5, 155);
	b.setSize(100, 40);
	auto f = [](const sgl::Event& e) {
		std::cout << "my own function was executed!" << std::endl;
	};
	b.addEventCallback(sgl::EventType::Button, f);

	// add checkbox to window
	sgl::Checkbox c(&w, "Check Me!");
	c.setPosition(200, 100);
	c.setSize(100, 40);

	//add textlabel to window
	sgl::TextLabel t(&w, "hello world");
	t.setPosition(10, 20);
	t.setSize(10, 10);

	//add textinput to window
	sgl::TextInput i(&w, "Der defaultText");
	i.setPosition(20,40);
	i.setSize(100,40);

	//add window with horizontal layout
	sgl::HBoxLayout hl(&w, "Horizontales Layout");
	hl.setPosition(0, 200);
	hl.setSize(400, 50);
	sgl::Button b2(&hl, "Press Me 2!");
	sgl::Button b3(&hl, "Press Me 3!");
	sgl::Button b4(&hl, "Press Me 4!");
	hl.updateLayout();

	// make everything visible
	gui.setVisible(true);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	gui.draw(renderer);
	SDL_RenderPresent(renderer);

	auto running = true;
	SDL_Event e;
	while (running)
	{
		while (0 != SDL_PollEvent(&e))
		{
			gui.handleEvent(e);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			gui.draw(renderer);
			SDL_RenderPresent(renderer);

			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}
	}

	// clean up allocated resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

	return 0;
}