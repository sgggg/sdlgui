#include "stdafx.h"
#include "RenderAssistant.h"

namespace sgl
{
	RenderAssistant::RenderAssistant()
		:graphicsResources_()
	{
		graphicsResources_.loadDefault();
	}

	SDL_Point RenderAssistant::renderCharacter(SDL_Renderer* renderer, char charToRender, int posX, int posY)
	{
		auto prerenderedChar = graphicsResources_.prerenderedCharacters_[charToRender].get();
		auto charTexture = SDL_CreateTextureFromSurface(renderer, prerenderedChar);
		if (charTexture == nullptr)
		{
			std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		auto ret = SDL_RenderCopy(renderer, charTexture, NULL, NULL);
		if (ret < 0)
		{
			std::cerr << "Unable to copy texture to renderer! Error: " << SDL_GetError() << std::endl;
		}
		return SDL_Point{ posX + prerenderedChar->w, posY + prerenderedChar->h };
	}

	SDL_Point RenderAssistant::renderString(SDL_Renderer* renderer, const std::string& stringToRender, int posX, int posY)
	{
		auto endOfString = SDL_Point{ posX, posY };
		for (auto character : stringToRender)
		{
			endOfString.x = posX;
			endOfString = renderCharacter(renderer, character, endOfString.x, endOfString.y);
		}
		return endOfString;
	}
}
