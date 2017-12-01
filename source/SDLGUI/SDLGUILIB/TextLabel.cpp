#include "stdafx.h"
#include "TextLabel.h"
#include "GuiManager.h"

namespace sgl
{
	TextLabel::TextLabel():
		Window(),
		text_(),
		text_alignment_(Alignment::Center)
	{
	}

	TextLabel::TextLabel(Window* parent, const std::string& text):
		Window(parent),
		text_(text),
		text_alignment_(Alignment::Center)
	{
	}

	std::string TextLabel::getText() const
	{
		return text_;
	}

	void TextLabel::setText(const std::string& new_text)
	{
		text_ = new_text;
	}

	Alignment TextLabel::getTextAlignment() const
	{
		return text_alignment_;
	}

	void TextLabel::setTextAlignment(Alignment alignment)
	{
		text_alignment_ = alignment;
	}

	void TextLabel::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			const auto aligned_point = getAlignedPointInRect({ screen_pos_.x, screen_pos_.y, size_.width, size_.height }, text_alignment_);
			if (is_active_)
			{
				renderTextAtPos(renderer, text_, aligned_point.x, aligned_point.y, text_alignment_, color_theme.text_active, color_theme.text_background);
			}
			else
			{
				renderTextAtPos(renderer, text_, aligned_point.x, aligned_point.y, text_alignment_, color_theme.text_inactive, color_theme.text_background);
			}
		}
	}
}
