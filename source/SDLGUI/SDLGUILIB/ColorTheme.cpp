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
		SDL_Color lightergray	= { 0xEE	,	0xEE	,	0xEE	, 0xFF	};
		SDL_Color lightgray		= { 0xDD	,	0xDD	,	0xDD	, 0xFF	};
		SDL_Color gray			= { 0xC0	,	0xC0	,	0xC0	, 0xFF	};
		SDL_Color darkergray	= { 0xAA	,	0xAA	,	0xAA	, 0xFF	};
		SDL_Color black			= { 0x0		,	0x0		,	0x0		, 0xFF	};
		SDL_Color white			= { 0xFF	,	0xFF	,	0xFF	, 0xFF	};
		SDL_Color transparent	= { 0x0		,	0x0		,	0x0		, 0x0	};
		windowBackground			= lightgray;
		windowTitlebar				= gray;
		windowFrameFocus			= black;
		windowFrameNoFocus			= lightgray;
		controlBackgroundActive		= lightgray;
		controlBackgroundInactive	= lightgray;
		controlFrameActive			= black;
		controlFrameInactive		= darkergray;
		controlContainsMouse		= lightergray;
		controlPressed				= darkergray;
		controlTextAreaBackground	= white;
		controlInputCursor			= black;
		textBackground				= transparent;
		textActive					= black;
		textInactive				= darkergray;
		textDefault					= darkergray;
	}

	GraphicsResources::GraphicsResources()
		:prerenderedCharacters_()
	{
	}

	static GraphicsResources::PrerendCharSet prerenderCharacters(const std::string& fontPath, int fontSize, 
		SDL_Color textColor, SDL_Color backgroundColor)
	{
		GraphicsResources::PrerendCharSet renderedCharacters;
		auto textFont = TTF_OpenFont(fontPath.c_str(), fontSize);
		if (textFont == nullptr)
		{
			std::cerr << "Unable to open font! Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			char charAsString[] = { '\0', '\0' };
			for (int i = 32; i <= 122; ++i)	// ASCII range of printable characters
			{
				charAsString[0] = static_cast<char>(i);
				auto surface = TTF_RenderText_Solid(textFont, charAsString, textColor);
				if (surface == nullptr)
				{
					std::cerr << "Unable to create surface from message! Error: " << SDL_GetError() << std::endl;
				}
				// auto texture = SDL_CreateTextureFromSurface(renderer, surface);
				// if (texture == nullptr)
				// {
				// 	std::cerr << "Unable to create texture from surface! Error: " << SDL_GetError() << std::endl;
				// }
				auto msurface = GraphicsResources::ManagedSurface(surface, SDL_FreeSurface);
				// auto mtexture = GraphicsResources::ManagedTexture(texture, SDL_DestroyTexture);
				renderedCharacters.emplace(std::make_pair(charAsString[0], std::move(msurface)));
			}
			TTF_CloseFont(textFont);
		}
		return renderedCharacters;
	}

	void GraphicsResources::loadDefault()
	{
		// prerender characters
		auto fontPath = getKnownFolderPath(KnownFolders::Fonts);
		// render with default color theme and style
		ColorTheme ctheme;
		WindowStyle wstyle;
		prerenderedCharacters_.emplace(TextMode::Active, prerenderCharacters(fontPath + "\\Arial.ttf", wstyle.fontSize, ctheme.textActive, ctheme.textBackground));
		prerenderedCharacters_.emplace(TextMode::Inactive, prerenderCharacters(fontPath + "\\Arial.ttf", wstyle.fontSize, ctheme.textInactive, ctheme.textBackground));
	}
}
