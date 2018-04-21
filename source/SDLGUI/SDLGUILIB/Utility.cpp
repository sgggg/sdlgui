#include "stdafx.h"

#include "Utility.h"
#include "OsUtility.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <cmath>				// provides pi

namespace sgl
{
	void alignRectangle(SDL_Rect& rect, Alignment new_alignment)
	{
		switch (new_alignment)
		{
		case Alignment::TopLeft:
			break;
		case Alignment::Top:
			rect.x -= rect.w / 2;
			break;
		case Alignment::TopRight:
			rect.x -= rect.w;
			break;
		case Alignment::Left:
			rect.y -= rect.h / 2;
			break;
		case Alignment::Center:
			rect.x -= rect.w / 2;
			rect.y -= rect.h / 2;
			break;
		case Alignment::Right:
			rect.x -= rect.w;
			rect.y -= rect.h / 2;
			break;
		case Alignment::BottomLeft:
			rect.y -= rect.h;
			break;
		case Alignment::Bottom:
			rect.x -= rect.w / 2;
			rect.y -= rect.h;
			break;
		case Alignment::BottomRight:
			rect.x -= rect.w;
			rect.y -= rect.h;
			break;
		default:
			break;
		}
	}

	Point getAlignedPointInRect(SDL_Rect rect, Alignment new_alignment)
	{
		auto new_point = Point{ rect.x, rect.y };
		switch (new_alignment)
		{
		case Alignment::TopLeft:
			break;
		case Alignment::Top:
			new_point.x = rect.x + rect.w / 2;
			break;
		case Alignment::TopRight:
			new_point.x = rect.x + rect.w;
			break;
		case Alignment::Left:
			new_point.y = rect.y + rect.h / 2;
			break;
		case Alignment::Center:
			new_point.x = rect.x + rect.w / 2;
			new_point.y = rect.y + rect.h / 2;
			break;
		case Alignment::Right:
			new_point.x = rect.x + rect.w;
			new_point.y = rect.y + rect.h / 2;
			break;
		case Alignment::BottomLeft:
			new_point.y = rect.y + rect.h;
			break;
		case Alignment::Bottom:
			new_point.x = rect.x + rect.w / 2;
			new_point.y = rect.y + rect.h;
			break;
		case Alignment::BottomRight:
			new_point.x = rect.x + rect.w;
			new_point.y = rect.y + rect.h;
			break;
		default:
			break;
		}
		return new_point;
	}
	
	void renderTextAtPos(SDL_Renderer* renderer, const std::string& text_message, int pos_x, int pos_y, Alignment align, SDL_Color text_color, SDL_Color background_color, int font_size)
	{
		auto font_path = getKnownFolderPath(KnownFolders::Fonts);
		auto text_font = TTF_OpenFont((font_path + "\\Arial.ttf").c_str(), font_size);

		if (text_font == NULL)
		{
			std::cerr << "Unable to open font! Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			auto surface_message = TTF_RenderText_Solid(text_font, text_message.c_str(), text_color);
			if (surface_message == NULL)
			{
				std::cerr << "renderTextAtPos(): Unable to create surface from message! Error: " << SDL_GetError() << std::endl;
			}
			else
			{
				// Get width and height from surface so we don't have to use SDL_QueryTexture
				const auto width = surface_message->w;
				const auto height = surface_message->h;

				auto texture_message = SDL_CreateTextureFromSurface(renderer, surface_message);
				if (texture_message == NULL)
				{
					std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
				}
				else
				{
					// Copy texture to renderer
					auto destination_rect = SDL_Rect{ pos_x, pos_y, width, height };
					alignRectangle(destination_rect, align);
					SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
					SDL_RenderFillRect(renderer, &destination_rect);
					SDL_RenderCopy(renderer, texture_message, NULL, &destination_rect);

					// Free resources
					SDL_DestroyTexture(texture_message);
				}
				SDL_FreeSurface(surface_message);
			}
			TTF_CloseFont(text_font);
		}
	}

	SDL_Surface* renderTextToSurface(const std::string& text_message, SDL_Color text_color, int font_size)
	{
		const auto font_path = getKnownFolderPath(KnownFolders::Fonts);
		auto text_font = TTF_OpenFont((font_path + "\\Arial.ttf").c_str(), font_size);
		SDL_Surface* surface = nullptr;
		if (text_font == NULL)
		{
			std::cerr << "Unable to open font! Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			surface = TTF_RenderText_Solid(text_font, text_message.c_str(), text_color);
			if (surface == NULL)
			{
				std::cerr << "renderTextToSurface(): Unable to create surface from message! Error: " << SDL_GetError() << std::endl;
			}
			TTF_CloseFont(text_font);
		}
		return surface;
	}

	void renderAndFreeSurface(SDL_Renderer* renderer, SDL_Surface* surface, int pos_x, int pos_y, Alignment align)
	{
		// Get width and height from surface so we don't have to use SDL_QueryTexture
		const auto width = surface->w;
		const auto height = surface->h;

		auto texture_message = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture_message == NULL)
		{
			std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Copy texture to renderer
			auto destination_rect = SDL_Rect{ pos_x, pos_y, width, height };
			alignRectangle(destination_rect, align);
			SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
			SDL_RenderCopy(renderer, texture_message, NULL, &destination_rect);

			// Free resources
			SDL_DestroyTexture(texture_message);
		}
		SDL_FreeSurface(surface);
	}

	void drawRectangle(SDL_Renderer* renderer, int pos_x, int pos_y, int width, int height, SDL_Color c)
	{
		const auto outline_rect = SDL_Rect{ pos_x, pos_y, width, height };
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		SDL_RenderDrawRect(renderer, &outline_rect);
	}

	void drawFilledRectangle(SDL_Renderer* renderer, int pos_x, int pos_y, int width, int height, SDL_Color c)
	{
		const auto outline_rect = SDL_Rect{ pos_x, pos_y, width, height };
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(renderer, &outline_rect);
	}

	void drawCircleImpl(SDL_Renderer* renderer, int x0, int y0, int radius, SDL_Color c, bool fill_circle)
	{
		// This function implements the Midpoint circle algorithm, 
		// see wikipedia https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
		// Note 1: There is a notation error on the wiki page in the C code example: they interchanged Octant 7 and 8
		// Note 2: To draw a filled circle, we simply connect two of the points we draw in opposite octants 
		// with horizontal lines.
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		auto x = radius;
		auto y = 0;
		auto decision_over_2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

		while (y <= x)
		{
			if (fill_circle)
			{
				SDL_RenderDrawLine(renderer, x0 + x, y0 + y, x0 - x, y0 + y);	// Octant 1 <-> 4
				SDL_RenderDrawLine(renderer, x0 + y, y0 + x, x0 - y, y0 + x);	// Octant 2 <-> 3
				SDL_RenderDrawLine(renderer, x0 - x, y0 - y, x0 + x, y0 - y);	// Octant 5 <-> 8
				SDL_RenderDrawLine(renderer, x0 - y, y0 - x, x0 + y, y0 - x);	// Octant 6 <-> 7
			}
			else
			{
				SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);		// Octant 1
				SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);		// Octant 2
				SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);		// Octant 3
				SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);		// Octant 4
				SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);		// Octant 5
				SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);		// Octant 6
				SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);		// Octant 7
				SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);		// Octant 8
			}
			y++;
			if (decision_over_2 <= 0)
			{
				decision_over_2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
			}
			else
			{
				x--;
				decision_over_2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
			}
		}
	}

	void drawCircle(SDL_Renderer* renderer, int circle_center_x, int circle_center_y, int radius, SDL_Color c)
	{
		drawCircleImpl(renderer, circle_center_x, circle_center_y, radius, c, false);
	}

	void drawFilledCircle(SDL_Renderer* renderer, int circle_center_x, int circle_center_y, int radius, SDL_Color c)
	{
		drawCircleImpl(renderer, circle_center_x, circle_center_y, radius, c, true);
	}
}