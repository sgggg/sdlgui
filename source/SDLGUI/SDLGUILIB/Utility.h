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

	void renderTextAtPos(SDL_Renderer* renderer, std::string textMessage, int posX, int posY, SDL_Color textColor = { 255,255,255,255 }, SDL_Color backgroundColor = {0,0,0,255}, int fontSize = 12);
	std::string ws2s(const std::wstring& wstr); // Converts wstring to string
}