#pragma once

#include "ColorTheme.h"

namespace sgl
{
	class StyleManager
	{
	public:
		StyleManager();

		const ColorTheme& getColorTheme() const;
		void loadDefaultColorTheme();

	private:
		ColorTheme currentColorTheme_;
	};
}
