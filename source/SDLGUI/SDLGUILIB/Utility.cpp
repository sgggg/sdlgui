#include "stdafx.h"

#include "Utility.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <codecvt>				// this is used in ws2s
#include <objbase.h>			// provides CoTaskMemFree
#include <Shlobj.h>				// provides SHGetKnownFolderPath
#include <Knownfolders.h>		// provides FOLDERID_Fonts
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

	void renderTextAtPos(SDL_Renderer* renderer, std::string textMessage, int posX, int posY, PosAlign align, SDL_Color textColor, SDL_Color backgroundColor, int fontSize)
	{
		wchar_t* folderPath;
		SHGetKnownFolderPath(FOLDERID_Fonts, 0, NULL, &folderPath);								// This stores the Windows folder path in folderPath
		auto textFont = TTF_OpenFont((ws2s(folderPath) + "\\Arial.ttf").c_str(), fontSize);	// We have to convert folderPath to string
		CoTaskMemFree(static_cast<void*>(folderPath));											// Manually free folderPath

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

	void drawCircle()
	{
		int centerOfCircle_x = 100, centerOfCircle_y = 100;// centre of circle in pixel coords
		int radius = 50;

		float pi = M_PI;

		float angleIncrease = 1.0f / radius;
		for (float angle = 0.0f; angle <= pi; angle += angleIncrease)
		{
			float xpos = centerOfCircle_x + radius*cos(angle);	// x position of pixel to be drawn
			float ypos = centerOfCircle_y + radius*sin(angle);	// y position of pixel to be drawn
			//putpixel(surface, xpos, ypos, pixel);
		}
	}

	/*
	* Set the pixel at (x, y) to the given value
	* NOTE: The surface must be locked before calling this!
	*/
	void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
	{
		int bpp = surface->format->BytesPerPixel;
		/* Here ppixel is the address to the pixel we want to set */
		Uint8 *ppixel = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

		switch (bpp) {
		case 1:
			*ppixel = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				ppixel[0] = (pixel >> 16) & 0xff;
				ppixel[1] = (pixel >> 8) & 0xff;
				ppixel[2] = pixel & 0xff;
			}
			else {
				ppixel[0] = pixel & 0xff;
				ppixel[1] = (pixel >> 8) & 0xff;
				ppixel[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)ppixel = pixel;
			break;
		}
	}


	std::string ws2s(const std::wstring& wstr)
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}
}