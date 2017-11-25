#pragma once

#include "SDL.h"
#include "../SDLGUILIB/EventProcessor.h"

void clickScreenPosition(int x, int y);

void typeText(sgl::EventProcessor& event_processor, const std::string& text_to_type);

SDL_Event leftMouseDown(int pos_x, int pos_y);
SDL_Event leftMouseUp(int pos_x, int pos_y);

