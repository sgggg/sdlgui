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
	
	// create new window
	sgl::Frame mainFrame(nullptr, "Main Window");
	mainFrame.setSize(400, 300);
	mainFrame.setTitleBarVisible(true);

	// add button to window
	sgl::Button b(&mainFrame, "Press Me!");
	b.setPosition(5, 155);
	b.setSize(100, 40);
	auto f1 = [](const sgl::Event& /*e*/) {
		std::cout << "\"Press Me!\" was clicked!" << std::endl;
	};
	b.addEventCallback(sgl::EventType::ButtonPressed, f1);

	// add checkbox to window
	sgl::Checkbox c(&mainFrame, "Hide Buttone \"Press Me!\"");
	c.setPosition(200, 100);
	c.setSize(100, 40);
	auto f2 = [&b](const sgl::Event& /*e*/) {
		std::cout << "checkbox checked" << std::endl;
		b.setVisible(false);
	};
	auto f3 = [&b](const sgl::Event& /*e*/) {
		std::cout << "checkbox unchecked" << std::endl;
		b.setVisible(true);
	};
	c.addEventCallback(sgl::EventType::CheckBoxChecked, f2);
	c.addEventCallback(sgl::EventType::CheckBoxUnchecked, f3);

	//add textlabel to window
	sgl::TextLabel t(&mainFrame, "hello world");
	t.setPosition(10, 20);
	t.setSize(10, 10);

	//add textinput to window
	sgl::TextInput i(&mainFrame, "Der defaultText");
	i.setPosition(20,40);
	i.setSize(100,40);

	//add window with grid layout
	sgl::GridLayout gl(&mainFrame);
	gl.setPosition(0, 200);
	gl.setSize(400, 100);
	sgl::Button b2(&gl, "Press Me 2!");
	sgl::Button b3(&gl, "Press Me 3!");
	sgl::Button b4(&gl, "Press Me 4!");
	gl.setGridPosition(b2, 1, 1);
	gl.setGridPosition(b3, 0, 0);
	gl.setGridPosition(b4, 0, 1);
	gl.updateLayout();

	// make everything visible
	mainFrame.setVisible(true);

	// create second window
	sgl::Frame secondFrame(nullptr, "Other Window");
	secondFrame.setSize(400, 300);
	secondFrame.setPosition(100, 100);
	secondFrame.setTitleBarVisible(true);
	secondFrame.setVisible(true);

	SDL_SetRenderDrawColor(renderer, 0, 0, 70, 255);
	SDL_RenderClear(renderer);
	sgl::DrawGui(renderer);
	SDL_RenderPresent(renderer);

	auto running = true;
	SDL_Event e;
	while (running)
	{
		while (0 != SDL_PollEvent(&e))
		{
			sgl::HandleEvent(&e);
			SDL_SetRenderDrawColor(renderer, 0, 0, 70, 255);
			SDL_RenderClear(renderer);
			sgl::DrawGui(renderer);
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