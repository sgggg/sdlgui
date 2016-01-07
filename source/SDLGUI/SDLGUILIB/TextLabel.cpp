#include "stdafx.h"
#include "TextLabel.h"
#include "Gui.h"

namespace sgl
{
	TextLabel::TextLabel()
		:Window()
		,text_()
	{
	}

	TextLabel::TextLabel(Window* parent, const std::string& text)
		:Window(parent)
		,text_(text)
	{
	}

	void TextLabel::setText(const std::string & newText)
	{
		text_ = newText;
	}

	void TextLabel::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			if (isActive_)
			{
				auto colorTheme = guiRoot_->getStyleManager().getColorTheme();
				renderTextAtPos(renderer, text_, screenPosX_, screenPosY_, PosAlign::TopLeft, colorTheme.textActive, colorTheme.textBackground);
			}
			else
			{
				// TODO draw inactive text (grayed out)
			}
		}
	}
}
