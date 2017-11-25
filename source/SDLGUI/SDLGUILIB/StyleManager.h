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
		void load_default_color_theme();
		void load_default_window_style();

	private:
		ColorTheme current_color_theme_;
		WindowStyle current_window_style_;
	};
}
