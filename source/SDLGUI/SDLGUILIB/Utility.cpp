#include "stdafx.h"

#include "Utility.h"
#include "SDL_ttf.h"
#include <iostream>

namespace sgl
{
	void renderTextAtPos(SDL_Renderer* renderer, std::string textMessage, int posX, int posY, PosAlign align, SDL_Color textColor, SDL_Color backgroundColor, int fontSize)
	{
		// TODO position drawn text according to alignment
		auto textFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", fontSize); // This obviously only works on windows and if windows is installed in C:\Windows
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
					SDL_Rect destRect = { posX, posY, width, height };
					SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
					SDL_RenderFillRect(renderer, &destRect);
					SDL_RenderCopy(renderer, textureMessage, NULL, &destRect);

					// Free resources
					SDL_FreeSurface(surfaceMessage);
					SDL_DestroyTexture(textureMessage);
					TTF_CloseFont(textFont);
				}
			}
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
}
