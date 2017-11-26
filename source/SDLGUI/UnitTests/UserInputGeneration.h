#pragma once

#include "SDL.h"
#include "../SDLGUILIB/EventProcessor.h"
#include "../SDLGUILIB/Window.h"

void globalClickScreenPosition(int x, int y);
void globalClickWindow(sgl::Window& window_to_click);

void localClickWindow(sgl::Window& window_to_click);

void moveCursorLeft(sgl::EventProcessor& event_processor, int num_spaces);
void moveCursorRight(sgl::EventProcessor& event_processor, int num_spaces);
void typeText(sgl::EventProcessor& event_processor, const std::string& text_to_type);
void typeBackspace(sgl::EventProcessor& event_processor, int num_spaces);
void typeDelete(sgl::EventProcessor& event_processor, int num_spaces);

SDL_Event leftMouseDown(int pos_x, int pos_y);
SDL_Event leftMouseUp(int pos_x, int pos_y);
SDL_Event pressCharacterKey(char character);

