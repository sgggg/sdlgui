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
	}

	const ColorTheme& StyleManager::getColorTheme() const
	{
		return currentColorTheme_;
	}

	void StyleManager::loadDefaultColorTheme()
	{
		currentColorTheme_.loadDefault();
	}
}
