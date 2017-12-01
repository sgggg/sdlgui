#include "stdafx.h"
#include "TextLabel.h"
#include "GuiManager.h"

namespace sgl
{
	TextLabel::TextLabel():
		Window(),
		label_(),
		label_alignment_(Alignment::Center)
	{
	}

	TextLabel::TextLabel(Window* parent, const std::string& text):
		Window(parent),
		label_(text),
		label_alignment_(Alignment::Center)
	{
	}

	std::string TextLabel::getLabel() const
	{
		return label_;
	}

	void TextLabel::setLabel(const std::string& new_text)
	{
		label_ = new_text;
	}

	Alignment TextLabel::getLabelAlignment() const
	{
		return label_alignment_;
	}

	void TextLabel::setLabelAlignment(Alignment alignment)
	{
		label_alignment_ = alignment;
	}

	void TextLabel::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			const auto aligned_point = getAlignedPointInRect({ screen_pos_.x, screen_pos_.y, size_.width, size_.height }, label_alignment_);
			if (is_active_)
			{
				renderTextAtPos(renderer, label_, aligned_point.x, aligned_point.y, label_alignment_, color_theme.text_active, color_theme.text_background);
			}
			else
			{
				renderTextAtPos(renderer, label_, aligned_point.x, aligned_point.y, label_alignment_, color_theme.text_inactive, color_theme.text_background);
			}
		}
	}
}
