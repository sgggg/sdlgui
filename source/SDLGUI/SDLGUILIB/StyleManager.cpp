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
		loadDefaultColorTheme();
		loadDefaultWindowStyle();
	}

	const ColorTheme& StyleManager::getColorTheme() const
	{
		return current_color_theme_;
	}

	const WindowStyle& StyleManager::getWindowStyle() const
	{
		return current_window_style_;
	}

	void StyleManager::loadDefaultColorTheme()
	{
		current_color_theme_.loadDefault();
	}

	void StyleManager::loadDefaultWindowStyle()
	{
		current_window_style_ = WindowStyle{};
	}
}
