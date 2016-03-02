#include "stdafx.h"
#include "RenderAssistant.h"

namespace sgl
{
	RenderAssistant::RenderAssistant()
		:graphicsResources_()
	{
		graphicsResources_.loadDefault();
	}

	SDL_Point RenderAssistant::renderCharacter(SDL_Renderer* renderer, char charToRender, TextMode mode, int posX, int posY) const
	{
		const auto prerenderedChar = graphicsResources_.prerenderedCharacters_.find(mode)->second.find(charToRender)->second.get();
		auto charTexture = SDL_CreateTextureFromSurface(renderer, prerenderedChar);
		if (charTexture == nullptr)
		{
			std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		auto charDestRect = SDL_Rect{posX, posY, prerenderedChar->w, prerenderedChar->h };
		auto ret = SDL_RenderCopy(renderer, charTexture, NULL, &charDestRect);
		if (ret < 0)
		{
			std::cerr << "Unable to copy texture to renderer! Error: " << SDL_GetError() << std::endl;
		}
		SDL_DestroyTexture(charTexture);
		return SDL_Point{ posX + prerenderedChar->w, posY + prerenderedChar->h };
	}

	SDL_Point RenderAssistant::renderString(SDL_Renderer* renderer, const std::string& stringToRender, TextMode mode, int posX, int posY) const
	{
		auto endOfString = SDL_Point{ posX, posY };
		for (const auto character : stringToRender)
		{
			endOfString.y = posY;
			endOfString = renderCharacter(renderer, character, mode, endOfString.x, endOfString.y);
		}
		return endOfString;
	}
}
