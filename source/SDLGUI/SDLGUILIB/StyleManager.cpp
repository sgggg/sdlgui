#include "stdafx.h"
#include "StyleManager.h"
#include "stdafx.h"

#include "StyleManager.h"

namespace sgl
{
	StyleManager::StyleManager()
		:current_color_theme_()
		,current_window_style_()
	{
		load_default_color_theme();
		load_default_window_style();
	}

	const ColorTheme& StyleManager::getColorTheme() const
	{
		return current_color_theme_;
	}

	const WindowStyle& StyleManager::getWindowStyle() const
	{
		return current_window_style_;
	}

	void StyleManager::load_default_color_theme()
	{
		current_color_theme_.loadDefault();
	}

	void StyleManager::load_default_window_style()
	{
		current_window_style_ = WindowStyle{};
	}
}
