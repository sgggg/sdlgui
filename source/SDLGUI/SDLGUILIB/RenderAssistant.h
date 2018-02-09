#pragma once

#include "ColorTheme.h"

namespace sgl
{
	class RenderAssistant
	{
	public:
		RenderAssistant();

		SDL_Point renderCharacter(SDL_Renderer* renderer, char char_to_render, TextMode mode, SDL_Point position) const;
		SDL_Point renderString(SDL_Renderer* renderer, const std::string& string_to_render, TextMode mode, int pos_x, int pos_y) const;

	private:
		SDL_Surface* getPrerenderedCharacter(sgl::TextMode &mode, char char_to_render) const;

		GraphicsResources graphics_resources_;
	};
}
