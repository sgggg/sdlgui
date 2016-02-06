#pragma once

#include "SDL.h"

namespace sgl
{
	class ColorTheme
	{
	public:
		ColorTheme();

		void loadDefault();

		SDL_Color windowBackground;
		SDL_Color windowTitlebar;
		SDL_Color windowFrameFocus;
		SDL_Color windowFrameNoFocus;
		SDL_Color controlBackgroundActive;
		SDL_Color controlBackgroundInactive;
		SDL_Color controlFrameActive;
		SDL_Color controlFrameInactive;
		SDL_Color controlContainsMouse;
		SDL_Color controlPressed;
		SDL_Color controlTextAreaBackground;
		SDL_Color controlInputCursor;
		SDL_Color textBackground;
		SDL_Color textActive;
		SDL_Color textInactive;
		SDL_Color textDefault;
		
	};

	class WindowStyle
	{
	public:
		int fontSize				= 12;
		int frameBorderSize			= 3;
		int buttonBorderSize		= 1;
		int innerPadding			= 2;
	};
}
