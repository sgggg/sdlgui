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

	void TextLabel::setText(const std::string & new_text)
	{
		text_ = new_text;
	}

	void TextLabel::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			if (is_active_)
			{
				renderTextAtPos(renderer, text_, screen_pos_.x, screen_pos_.y, PosAlign::TopLeft, color_theme.text_active, color_theme.text_background);
			}
			else
			{
				renderTextAtPos(renderer, text_, screen_pos_.x, screen_pos_.y, PosAlign::TopLeft, color_theme.text_inactive, color_theme.text_background);
			}
		}
	}
}
