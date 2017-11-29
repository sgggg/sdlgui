#include "stdafx.h"
#include "ColorTheme.h"
#include "Utility.h"
#include "OsUtility.h"
#include "SDL_ttf.h"

namespace sgl
{
	ColorTheme::ColorTheme()
	{
		loadDefault();
	}

	void ColorTheme::loadDefault()
	{
		const SDL_Color lightergray		= { 0xEE	,	0xEE	,	0xEE	, 0xFF	};
		const SDL_Color lightgray		= { 0xDD	,	0xDD	,	0xDD	, 0xFF	};
		const SDL_Color gray			= { 0xC0	,	0xC0	,	0xC0	, 0xFF	};
		const SDL_Color darkergray		= { 0xAA	,	0xAA	,	0xAA	, 0xFF	};
		const SDL_Color black			= { 0x0		,	0x0		,	0x0		, 0xFF	};
		const SDL_Color white			= { 0xFF	,	0xFF	,	0xFF	, 0xFF	};
		const SDL_Color transparent		= { 0x0		,	0x0		,	0x0		, 0x0	};
		window_background				= lightgray;
		window_titlebar					= gray;
		window_frame_focus				= black;
		window_frame_no_focus			= lightgray;
		control_background_active		= lightgray;
		control_background_inactive		= lightgray;
		control_frame_active			= black;
		control_frame_inactive			= darkergray;
		control_contains_mouse			= lightergray;
		control_pressed					= darkergray;
		control_text_area_background	= white;
		control_input_cursor			= black;
		text_background					= transparent;
		text_active						= black;
		text_inactive					= darkergray;
		text_default					= darkergray;
	}

	GraphicsResources::GraphicsResources()
		:prerendered_characters_()
	{
	}

	static GraphicsResources::PrerendCharSet prerenderCharacters(const std::string& font_path, int font_size, 
		SDL_Color text_color, SDL_Color background_color)
	{
		GraphicsResources::PrerendCharSet rendered_characters;
		auto text_font = TTF_OpenFont(font_path.c_str(), font_size);
		if (text_font == nullptr)
		{
			std::cerr << "Unable to open font! Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			char char_as_string[] = { '\0', '\0' };
			for (int i = 32; i <= 122; ++i)	// ASCII range of printable characters
			{
				char_as_string[0] = static_cast<char>(i);
				auto surface = TTF_RenderText_Solid(text_font, char_as_string, text_color);
				if (surface == nullptr)
				{
					std::cerr << "Unable to create surface from message! Error: " << SDL_GetError() << std::endl;
				}
				auto managed_surface = GraphicsResources::ManagedSurface(surface, SDL_FreeSurface);
				rendered_characters.emplace(std::make_pair(char_as_string[0], std::move(managed_surface)));
			}
			TTF_CloseFont(text_font);
		}
		return rendered_characters;
	}

	void GraphicsResources::loadDefault()
	{
		// prerender characters
		const auto fontPath = getKnownFolderPath(KnownFolders::Fonts);
		// render with default color theme and style
		ColorTheme ctheme;
		WindowStyle wstyle;
		prerendered_characters_.emplace(TextMode::Active, prerenderCharacters(fontPath + "\\Arial.ttf", wstyle.font_size, ctheme.text_active, ctheme.text_background));
		prerendered_characters_.emplace(TextMode::Inactive, prerenderCharacters(fontPath + "\\Arial.ttf", wstyle.font_size, ctheme.text_inactive, ctheme.text_background));
	}
}
