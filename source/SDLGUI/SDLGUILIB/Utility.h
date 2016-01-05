#pragma once

#include "SDL.h"

namespace sgl
{
	struct Point
	{
		int x;
		int y;
	};

	struct Size
	{
		int width;
		int height;
	};

	enum class PosAlign
	{
		Center, 
		Top, 
		Bottom, 
		Left, 
		Right,
		TopRight,
		TopLeft,
		BottomRight,
		BottomLeft
	};

	void renderTextAtPos(SDL_Renderer* renderer, std::string textMessage, int posX, int posY, PosAlign align = PosAlign::TopLeft,
		SDL_Color textColor = { 255,255,255 }, SDL_Color backgroundColor = {0,0,0}, int fontSize = 12);

	void drawRectangle(SDL_Renderer* renderer, int posX, int posY, int width, int height, SDL_Color c);

	void drawFilledRectangle(SDL_Renderer* renderer, int posX, int posY, int width, int height, SDL_Color c);
}