#pragma once

#include "SDL.h"

namespace sgl
{
	struct Point
	{
		int x;
		int y;
	};

	inline bool operator==(Point lhs, Point rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	inline Point operator+(Point lhs, Point rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	inline Point operator-(Point lhs, Point rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
	}

	struct Size
	{
		int width;
		int height;
	};

	inline bool operator==(Size lhs, Size rhs)
	{
		return lhs.width == rhs.width && lhs.height == rhs.height;
	}

	enum class Alignment
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

	void alignRectangle(SDL_Rect& rect, Alignment new_alignment);
	Point getAlignedPointInRect(SDL_Rect rect, Alignment new_alignment);

	inline Point getCenter(SDL_Rect rect)
	{
		return { rect.x + rect.w / 2, rect.y + rect.h / 2 };
	}

	void renderTextAtPos(SDL_Renderer* renderer, const std::string& text_message, int pos_x, int pos_y, Alignment align = Alignment::TopLeft,
		SDL_Color text_color = { 255, 255, 255, 255 }, SDL_Color background_color = { 0, 0, 0, 255 }, int font_size = 12);

	SDL_Surface* renderTextToSurface(const std::string& text_message, SDL_Color text_color = { 255, 255, 255, 255 }, int font_size = 12);

	void renderAndFreeSurface(SDL_Renderer* renderer, SDL_Surface* surface, int pos_x, int pos_y, Alignment align = Alignment::TopLeft);

	void drawRectangle(SDL_Renderer* renderer, int pos_x, int pos_y, int width, int height, SDL_Color c);

	void drawFilledRectangle(SDL_Renderer* renderer, int pos_x, int pos_y, int width, int height, SDL_Color c);

	void drawCircle(SDL_Renderer* renderer, int circle_center_x, int circle_center_y, int radius, SDL_Color c);

	void drawFilledCircle(SDL_Renderer* renderer, int circle_center_x, int circle_center_y, int radius, SDL_Color c);
}
