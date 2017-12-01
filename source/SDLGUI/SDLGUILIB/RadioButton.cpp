#include "stdafx.h"
#include "RadioButton.h"
#include "GuiManager.h"

namespace sgl
{
	RadioButton::RadioButton()
		:Window()
		, label_()
		, is_checked_(false)
	{
	}

	RadioButton::RadioButton(Window* parent, const std::string& label)
		:Window(parent)
		, label_(label)
		, is_checked_(false)
	{
	}

	std::string RadioButton::getLabel() const
	{
		return label_;
	}

	void RadioButton::setLabel(const std::string& text)
	{
		label_ = text;
	}

	bool RadioButton::isChecked() const
	{
		return is_checked_;
	}

	void RadioButton::setChecked(bool is_checked)
	{
		is_checked_ = is_checked;
	}

	void RadioButton::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			constexpr auto box_size = 12;
			constexpr auto label_offset = 8 + box_size;
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			const auto circle_center_x = screen_pos_.x + box_size / 2;
			const auto circle_center_y = screen_pos_.y + box_size / 2;
			const auto circle_radius = box_size / 2;

			if (is_active_)
			{
				// draw circle
				if (contains_mouse_)
				{
					drawFilledCircle(renderer, circle_center_x, circle_center_y, circle_radius, color_theme.control_contains_mouse);
				}
				else
				{
					drawFilledCircle(renderer, circle_center_x, circle_center_y, circle_radius, color_theme.control_background_active);
				}
				drawCircle(renderer, circle_center_x, circle_center_y, circle_radius, color_theme.control_frame_active);
				if (is_checked_)
				{
					drawFilledCircle(renderer, circle_center_x, circle_center_y, circle_radius - 2, color_theme.control_frame_active);
				}
				else
				{
					// draw in unchecked state -> no fill
				}
				// draw label next to control
				renderTextAtPos(renderer, label_, screen_pos_.x + label_offset, screen_pos_.y + circle_radius, Alignment::Left, color_theme.text_active, color_theme.text_background);
			}
			else
			{
				// TODO draw in inactive state (grayed out)
			}
		}
	}

	void RadioButton::triggerClicked()
	{
		is_checked_ = !is_checked_;
		const auto event_type = is_checked_ ? EventType::RadioButtonChecked : EventType::RadioButtonChecked;
		auto event_handler = event_handlers_.find(event_type);
		if (event_handler != std::end(event_handlers_))
		{
			Event e;
			e.type_ = event_type;
			e.time_ = manager_->getApplicationTime().count();
			event_handler->second(e);
		}
	}
}
