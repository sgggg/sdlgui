#include "stdafx.h"
#include "TextLabel.h"
#include "gui.h"

namespace sgl
{
	TextLabel::TextLabel()
		:Window()
	{
	}

	TextLabel::TextLabel(Window* parent, const std::string& text)
		:Window(parent, text)
	{
	}

	void TextLabel::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			if (isActive_)
			{
				auto colorTheme = guiRoot_->getStyleManager().getColorTheme();
				renderTextAtPos(renderer, label_, screenPosX_, screenPosY_, PosAlign::TopLeft, colorTheme.textActive, colorTheme.textBackground);
			}
			else
			{
				// TODO draw inactive text (grayed out)
			}
		}
	}
}
