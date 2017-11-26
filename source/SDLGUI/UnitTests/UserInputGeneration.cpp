#include "stdafx.h"
#include "UserInputGeneration.h"
#include "../SDLGUILIB/SGL.h"

void clickScreenPosition(int x, int y)
{
	auto press = leftMouseDown(x, y);
	auto release = leftMouseUp(x, y);
	sgl::HandleEvent(&press);
	sgl::HandleEvent(&release);
}

void clickOnWindow(sgl::Window& window_to_click)
{
	auto position = window_to_click.getPosition();
	auto size = window_to_click.getSize();
	auto center_of_window = sgl::Point{position.x + size.width / 2, position.y + size.height / 2};
	auto press = leftMouseDown(center_of_window.x, center_of_window.y);
	auto release = leftMouseUp(center_of_window.x, center_of_window.y);
	sgl::HandleEvent(&press);
	sgl::HandleEvent(&release);
}

void typeText(sgl::EventProcessor& event_processor, const std::string& text_to_type)
{
	for (auto character : text_to_type)
	{
		auto key_press_event = pressCharacterKey(character);
		event_processor.handleEvent(key_press_event);
	}
}

void moveCursorLeft(sgl::EventProcessor & event_processor, int num_spaces)
{
	for (auto i = 0; i < num_spaces; ++i)
	{
		auto key_press_event = SDL_Event{};
		key_press_event.type = SDL_KEYDOWN;
		key_press_event.key.keysym.scancode = SDL_SCANCODE_LEFT;
		key_press_event.key.keysym.sym = SDLK_LEFT;
		key_press_event.key.keysym.mod = 0;
		event_processor.handleEvent(key_press_event);
	}
}

void moveCursorRight(sgl::EventProcessor & event_processor, int num_spaces)
{
	for (auto i = 0; i < num_spaces; ++i)
	{
		auto key_press_event = SDL_Event{};
		key_press_event.type = SDL_KEYDOWN;
		key_press_event.key.keysym.scancode = SDL_SCANCODE_RIGHT;
		key_press_event.key.keysym.sym = SDLK_RIGHT;
		key_press_event.key.keysym.mod = 0;
		event_processor.handleEvent(key_press_event);
	}
}

void typeBackspace(sgl::EventProcessor & event_processor, int num_spaces)
{
	for (auto i = 0; i < num_spaces; ++i)
	{
		auto key_press_event = SDL_Event{};
		key_press_event.type = SDL_KEYDOWN;
		key_press_event.key.keysym.scancode = SDL_SCANCODE_BACKSPACE;
		key_press_event.key.keysym.sym = SDLK_BACKSPACE;
		key_press_event.key.keysym.mod = 0;
		event_processor.handleEvent(key_press_event);
	}
}

void typeDelete(sgl::EventProcessor & event_processor, int num_spaces)
{
	for (auto i = 0; i < num_spaces; ++i)
	{
		auto key_press_event = SDL_Event{};
		key_press_event.type = SDL_KEYDOWN;
		key_press_event.key.keysym.scancode = SDL_SCANCODE_DELETE;
		key_press_event.key.keysym.sym = SDLK_DELETE;
		key_press_event.key.keysym.mod = 0;
		event_processor.handleEvent(key_press_event);
	}
}

SDL_Event leftMouseDown(int pos_x, int pos_y)
{
	auto press_event = SDL_Event{};
	press_event.type = SDL_MOUSEBUTTONDOWN;
	press_event.button.x = pos_x;
	press_event.button.y = pos_y;
	press_event.button.state = SDL_PRESSED;
	press_event.button.button = SDL_BUTTON_LEFT;
	return press_event;
}

SDL_Event leftMouseUp(int pos_x, int pos_y)
{
	auto release_event = SDL_Event{};
	release_event.type = SDL_MOUSEBUTTONUP;
	release_event.button.x = pos_x;
	release_event.button.y = pos_y;
	release_event.button.state = SDL_RELEASED;
	release_event.button.button = SDL_BUTTON_LEFT;
	return release_event;
}

SDL_Event pressCharacterKey(char character)
{
	if (character < 13 || character > 122)
	{
		throw std::runtime_error("typing this key is not supported right now");
	}
	Uint16 modifier{};
	if (character >= 'A' && character <= 'Z')
	{
		character += 'a' - 'A';
		modifier = KMOD_SHIFT;
	}
	auto key_press_event = SDL_Event{};
	key_press_event.type = SDL_KEYDOWN;
	key_press_event.key.keysym.scancode = {};	// currently not set!
	key_press_event.key.keysym.sym = static_cast<SDL_Keycode>(character);
	key_press_event.key.keysym.mod = modifier;
	key_press_event.key.keysym.unused = {};
	return key_press_event;
}


