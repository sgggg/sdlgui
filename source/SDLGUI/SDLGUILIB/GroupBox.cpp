#include "stdafx.h"
#include "GroupBox.h"
#include "GuiManager.h"

namespace sgl
{
	GroupBox::GroupBox() :
		Window(),
		label_()
	{
	}

	GroupBox::GroupBox(Window* parent) :
		Window(parent),
		label_()
	{
	}

	std::string GroupBox::getLabel() const
	{
		return label_;
	}

	void GroupBox::setLabel(const std::string& new_text)
	{
		label_ = new_text;
	}

	void GroupBox::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			SDL_Color color_button_fill, color_frame, color_label;
			if (is_active_)
			{
				color_frame = color_theme.control_frame_active;
				color_label = color_theme.text_active;
			}
			else
			{
				color_frame = color_theme.control_frame_inactive;
				color_label = color_theme.text_inactive;
			}
			drawRectangle(renderer, screen_pos_.x, screen_pos_.y, size_.width, size_.height, color_frame);

			const auto aligned_point = getAlignedPointInRect({ screen_pos_.x, screen_pos_.y, size_.width, size_.height }, Alignment::TopLeft);
			// renderTextAtPos(renderer, label_, aligned_point.x, aligned_point.y, Alignment::TopLeft, color_label, color_theme.text_background);

			for (const auto& child : children_)
			{
				child->draw(renderer);
			}
		}
	}
}
