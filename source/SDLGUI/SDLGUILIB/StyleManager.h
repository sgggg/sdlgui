#pragma once

#include "ColorTheme.h"

namespace sgl
{
	class StyleManager
	{
	public:
		StyleManager();

		const ColorTheme& getColorTheme() const;
		const WindowStyle& getWindowStyle() const;
		void loadDefaultColorTheme();
		void loadDefaultWindowStyle();

	private:
		ColorTheme current_color_theme_;
		WindowStyle current_window_style_;
	};
}
