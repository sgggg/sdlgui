#include "stdafx.h"
#include "StyleManager.h"
#include "stdafx.h"

#include "StyleManager.h"

namespace sgl
{
	StyleManager::StyleManager()
		:currentColorTheme_()
	{
		loadDefaultColorTheme();
		loadDefaultWindowStyle();
	}

	const ColorTheme& StyleManager::getColorTheme() const
	{
		return currentColorTheme_;
	}

	const WindowStyle & StyleManager::getWindowStyle() const
	{
		return currentWindowStyle_;
	}

	void StyleManager::loadDefaultColorTheme()
	{
		currentColorTheme_.loadDefault();
	}
	void StyleManager::loadDefaultWindowStyle()
	{
		currentWindowStyle_ = WindowStyle();
	}
}
