#pragma once

#include "SDL.h"
#include <functional>
#include <map>
#include <memory>

namespace sgl
{
	enum class TextMode
	{
		Active,
		Inactive
	};

	class ColorTheme
	{
	public:
		ColorTheme();

		void loadDefault();

		SDL_Color window_background;
		SDL_Color window_titlebar;
		SDL_Color window_frame_focus;
		SDL_Color window_frame_no_focus;
		SDL_Color control_background_active;
		SDL_Color control_background_inactive;
		SDL_Color control_frame_active;
		SDL_Color control_frame_inactive;
		SDL_Color control_contains_mouse;
		SDL_Color control_pressed;
		SDL_Color control_text_area_background;
		SDL_Color control_input_cursor;
		SDL_Color text_background;
		SDL_Color text_active;
		SDL_Color text_inactive;
		SDL_Color text_default;
		
	};

	class WindowStyle
	{
	public:
		int font_size				= 12;
		int frame_border_size		= 3;
		int button_border_size		= 1;
		int inner_padding			= 4;
		int checkbox_size			= 12;
	};

	class GraphicsResources
	{
	public:
		typedef std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>> ManagedSurface;
		typedef std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>> ManagedTexture;
		typedef std::map<char, ManagedSurface> PrerendCharSet;
		typedef std::map<TextMode, PrerendCharSet> PrerendCharMap;
		
		GraphicsResources();

		void loadDefault();

		PrerendCharMap prerendered_characters_;
	};
}
