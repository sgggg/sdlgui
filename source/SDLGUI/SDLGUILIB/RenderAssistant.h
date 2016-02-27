#pragma once

#include "ColorTheme.h"

namespace sgl
{
	class RenderAssistant
	{
	public:
		RenderAssistant();

		SDL_Point renderCharacter(SDL_Renderer* renderer, char charToRender, int posX, int posY);
		SDL_Point renderString(SDL_Renderer* renderer, const std::string& stringToRender, int posX, int posY);

	private:
		GraphicsResources graphicsResources_;
	};
}
