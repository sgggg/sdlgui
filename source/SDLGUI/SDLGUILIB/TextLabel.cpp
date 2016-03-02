#include "stdafx.h"
#include "TextLabel.h"
#include "GuiManager.h"

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

	std::string TextLabel::getText() const
	{
		return text_;
	}

	void TextLabel::setText(const std::string & newText)
	{
		text_ = newText;
	}

	void TextLabel::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			// auto& colorTheme = manager_->getStyleManager().getColorTheme();
			// auto& renderAssist = manager_->getRenderAssistant();
			// if (isActive_)
			// {
			// 	renderAssist.renderString(renderer, text_, TextMode::Active, screenPosX_, screenPosY_);
			// }
			// else
			// {
			// 	renderAssist.renderString(renderer, text_, TextMode::Inactive, screenPosX_, screenPosY_);
			// }
			auto& colorTheme = manager_->getStyleManager().getColorTheme();
			auto& renderAssist = manager_->getRenderAssistant();
			if (isActive_)
			{
				auto colorTheme = manager_->getStyleManager().getColorTheme();
				renderTextAtPos(renderer, text_, screenPosX_, screenPosY_, PosAlign::TopLeft, colorTheme.textActive, colorTheme.textBackground);
			}
			else
			{
				// TODO draw inactive text (grayed out)
			}
		}
	}
}
