#include "stdafx.h"
#include "UserInputGeneration.h"

SDL_Event leftMouseDown(int pos_x, int pos_y)
{
	auto press_event = SDL_Event{};
	press_event.type = SDL_MOUSEBUTTONDOWN;
	press_event.button.x = pos_x;
	press_event.button.x = pos_y;
	press_event.button.state = SDL_PRESSED;
	press_event.button.button = SDL_BUTTON_LEFT;
	return press_event;
}

SDL_Event leftMouseUp(int pos_x, int pos_y)
{
	auto release_event = SDL_Event{};
	release_event.type = SDL_MOUSEBUTTONUP;
	release_event.button.x = pos_x;
	release_event.button.x = pos_y;
	release_event.button.state = SDL_RELEASED;
	release_event.button.button = SDL_BUTTON_LEFT;
	return release_event;
}

