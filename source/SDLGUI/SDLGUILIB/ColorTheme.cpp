#include "stdafx.h"
#include "ColorTheme.h"

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
		SDL_Color white			= { 0xFF	,	0xFF	,	0xFF	, 0xFF };
		SDL_Color transparent	= { 0x0		,	0x0		,	0x0		, 0x0	};
		windowBackground			= lightgray;
		windowTitlebar				= gray;
		windowFrameFocus			= lightgray;
		windowFrameNoFocus			= lightgray;
		controlBackgroundActive		= lightgray;
		controlBackgroundInactive	= lightgray;
		controlFrameActive			= black;
		controlFrameInactive		= darkergray;
		controlContainsMouse		= lightergray;
		controlPressed				= darkergray;
		controlInputBackground		= white;
		textBackground				= transparent;
		textActive					= black;
		textInactive				= darkergray;
	}

}
