#include "stdafx.h"

#include "Utility.h"
#include "SDL_ttf.h"
#include <iostream>

namespace sgl
{
	void renderTextAtPos(SDL_Renderer* renderer, std::string textMessage, int posX, int posY, SDL_Color textColor, SDL_Color backgroundColor, int fontSize)
	{
		int width_, height_;

		auto textFont = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", fontSize);
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
				width_ = surfaceMessage->w;
				height_ = surfaceMessage->h;

				auto textureMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
				if (textureMessage == NULL)
				{
					std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
				}
				else
				{
					SDL_FreeSurface(surfaceMessage);

					SDL_Rect destRect = { posX, posY, width_, height_ };
					SDL_RenderFillRect(renderer, &destRect);
					SDL_RenderCopy(renderer, textureMessage, NULL, &destRect);
					SDL_DestroyTexture(textureMessage);
					TTF_CloseFont(textFont);
				}
			}
		}
	}
}
