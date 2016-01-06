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
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Point alignRectangle(SDL_Rect rect, PosAlign newAlignment);

	inline Point getCenter(SDL_Rect rect)
	{
		return { rect.x + rect.w / 2, rect.y + rect.h / 2 };
	}

	void renderTextAtPos(SDL_Renderer* renderer, std::string textMessage, int posX, int posY, PosAlign align = PosAlign::TopLeft,
		SDL_Color textColor = { 255,255,255 }, SDL_Color backgroundColor = {0,0,0}, int fontSize = 12);

	void drawRectangle(SDL_Renderer* renderer, int posX, int posY, int width, int height, SDL_Color c);

	void drawFilledRectangle(SDL_Renderer* renderer, int posX, int posY, int width, int height, SDL_Color c);

	std::string ws2s(const std::wstring& wstr); // Converts wstring to string
}