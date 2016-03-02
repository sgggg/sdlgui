#pragma once

#include "ColorTheme.h"

namespace sgl
{
	class RenderAssistant
	{
	public:
		RenderAssistant();

		SDL_Point renderCharacter(SDL_Renderer* renderer, char charToRender, TextMode mode, int posX, int posY) const;
		SDL_Point renderString(SDL_Renderer* renderer, const std::string& stringToRender, TextMode mode, int posX, int posY) const;

	private:
		GraphicsResources graphicsResources_;
	};
}
