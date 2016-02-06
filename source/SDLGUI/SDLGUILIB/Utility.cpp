#include "stdafx.h"

#include "Utility.h"
#include "OsUtility.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <codecvt>				// this is used in ws2s
#include <cmath>				// provides pi

namespace sgl
{
	Point alignRectangle(SDL_Rect rect, PosAlign newAlignment)
	{
		Point newPosition = { rect.x, rect.y };
		switch (newAlignment)
		{
		case PosAlign::TopLeft:
			break;
		case PosAlign::Top:
			newPosition.x = rect.x - rect.w / 2;
			break;
		case PosAlign::TopRight:
			newPosition.x = rect.x - rect.w;
			break;
		case PosAlign::Left:
			newPosition.y = rect.y - rect.h / 2;
			break;
		case PosAlign::Center:
			newPosition.x = rect.x - rect.w / 2;
			newPosition.y = rect.y - rect.h / 2;
			break;
		case PosAlign::Right:
			newPosition.x = rect.x - rect.w;
			newPosition.y = rect.y - rect.h / 2;
			break;
		case PosAlign::BottomLeft:
			newPosition.y = rect.y - rect.h;
			break;
		case PosAlign::Bottom:
			newPosition.x = rect.x - rect.w / 2;
			newPosition.y = rect.y - rect.h;
			break;
		case PosAlign::BottomRight:
			newPosition.x = rect.x - rect.w;
			newPosition.y = rect.y - rect.h;
			break;
		default:
			break;
		}
		return newPosition;
	}

	void renderTextAtPos(SDL_Renderer* renderer, const std::string& textMessage, int posX, int posY, PosAlign align, SDL_Color textColor, SDL_Color backgroundColor, int fontSize)
	{
		auto fontPath = getKnownFolderPath(KnownFolders::Fonts);
		auto textFont = TTF_OpenFont((fontPath + "\\Arial.ttf").c_str(), fontSize);

		if (textFont == NULL)
		{
			std::cerr << "Unable to open font! Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			auto surfaceMessage = TTF_RenderText_Solid(textFont, textMessage.c_str(), textColor);
			if (surfaceMessage == NULL)
			{
				std::cerr << "Unable to create surface from message! Error: " << SDL_GetError() << std::endl;
			}
			else
			{
				// Get width and height from surface so we don't have to use SDL_QueryTexture
				auto width = surfaceMessage->w;
				auto height = surfaceMessage->h;

				auto textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
				if (textureMessage == NULL)
				{
					std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
				}
				else
				{
					// Copy texture to renderer
					auto alignedPos = alignRectangle({ posX, posY, width, height }, align);
					SDL_Rect destRect = { alignedPos.x, alignedPos.y, width, height };
					SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
					SDL_RenderFillRect(renderer, &destRect);
					SDL_RenderCopy(renderer, textureMessage, NULL, &destRect);

					// Free resources
					SDL_DestroyTexture(textureMessage);
				}
				SDL_FreeSurface(surfaceMessage);
			}
			TTF_CloseFont(textFont);
		}
	}

	SDL_Surface* renderTextToSurface(const std::string& textMessage, SDL_Color textColor, int fontSize)
	{
		auto fontPath = getKnownFolderPath(KnownFolders::Fonts);
		auto textFont = TTF_OpenFont((fontPath + "\\Arial.ttf").c_str(), fontSize);
		SDL_Surface* surface = nullptr;
		if (textFont == NULL)
		{
			std::cerr << "Unable to open font! Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			surface = TTF_RenderText_Solid(textFont, textMessage.c_str(), textColor);
			if (surface == NULL)
			{
				std::cerr << "Unable to create surface from message! Error: " << SDL_GetError() << std::endl;
			}
			TTF_CloseFont(textFont);
		}
		return surface;
	}

	void renderAndFreeSurface(SDL_Renderer* renderer, SDL_Surface* surface, int posX, int posY, PosAlign align)
	{
		// Get width and height from surface so we don't have to use SDL_QueryTexture
		auto width = surface->w;
		auto height = surface->h;

		auto textureMessage = SDL_CreateTextureFromSurface(renderer, surface);
		if (textureMessage == NULL)
		{
			std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Copy texture to renderer
			auto alignedPos = alignRectangle({ posX, posY, width, height }, align);
			SDL_Rect destRect = { alignedPos.x, alignedPos.y, width, height };
			SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
			SDL_RenderCopy(renderer, textureMessage, NULL, &destRect);

			// Free resources
			SDL_DestroyTexture(textureMessage);
		}
		SDL_FreeSurface(surface);
	}

	void drawRectangle(SDL_Renderer* renderer, int posX, int posY, int width, int height, SDL_Color c)
	{
		SDL_Rect outlineRect = { posX, posY, width, height };
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		SDL_RenderDrawRect(renderer, &outlineRect);
	}

	void drawFilledRectangle(SDL_Renderer* renderer, int posX, int posY, int width, int height, SDL_Color c)
	{
		SDL_Rect outlineRect = { posX, posY, width, height };
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		SDL_RenderFillRect(renderer, &outlineRect);
	}

	void drawCircleImpl(SDL_Renderer* renderer, int x0, int y0, int radius, SDL_Color c, bool fillCircle)
	{
		// This function implements the Midpoint circle algorithm, 
		// see wikipedia https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
		// Note 1: There is a notation error on the wiki page in the C code example: they interchanged Octant 7 and 8
		// Note 2: To draw a filled circle, we simply connect two of the points we draw in opposite octants 
		// with horizontal lines.
		SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
		auto x = radius;
		auto y = 0;
		auto decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

		while (y <= x)
		{
			if (fillCircle)
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
			if (decisionOver2 <= 0)
			{
				decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
			}
			else
			{
				x--;
				decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
			}
		}
	}

	void drawCircle(SDL_Renderer* renderer, int circleCenterX, int circleCenterY, int radius, SDL_Color c)
	{
		drawCircleImpl(renderer, circleCenterX, circleCenterY, radius, c, false);
	}

	void drawFilledCircle(SDL_Renderer* renderer, int circleCenterX, int circleCenterY, int radius, SDL_Color c)
	{
		drawCircleImpl(renderer, circleCenterX, circleCenterY, radius, c, true);
	}
	
	std::string ws2s(const std::wstring& wstr)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}
}