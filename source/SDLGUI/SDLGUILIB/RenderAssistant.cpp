#include "stdafx.h"
#include "RenderAssistant.h"

namespace sgl
{
	RenderAssistant::RenderAssistant()
		:graphics_resources_()
	{
		graphics_resources_.loadDefault();
	}

	SDL_Point RenderAssistant::renderCharacter(SDL_Renderer* renderer, char char_to_render, TextMode mode, SDL_Point position) const
	{
		const auto prerendered_char = getPrerenderedCharacter(mode, char_to_render);
		auto char_texture = SDL_CreateTextureFromSurface(renderer, prerendered_char);
		if (char_texture == nullptr)
		{
			std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		auto char_dest_rect = SDL_Rect{position.x, position.y, prerendered_char->w, prerendered_char->h };
		auto ret = SDL_RenderCopy(renderer, char_texture, NULL, &char_dest_rect);
		if (ret < 0)
		{
			std::cerr << "Unable to copy texture to renderer! Error: " << SDL_GetError() << std::endl;
		}
		SDL_DestroyTexture(char_texture);
		return SDL_Point{ position.x + prerendered_char->w, position.y + prerendered_char->h };
	}

	SDL_Surface* RenderAssistant::getPrerenderedCharacter(sgl::TextMode& mode, char char_to_render) const
	{
		return graphics_resources_.prerendered_characters_.find(mode)->second.find(char_to_render)->second.get();
	}

	SDL_Point RenderAssistant::renderString(SDL_Renderer* renderer, const std::string& string_to_render, TextMode mode, int posX, int posY) const
	{
		return std::accumulate(string_to_render.begin(), string_to_render.end(), SDL_Point{posX, posY}, [=](auto draw_position, auto character) {
			draw_position.y = posY;
			return renderCharacter(renderer, character, mode, draw_position);
		});
	}
}
