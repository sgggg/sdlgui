
#include "stdafx.h"
#include "RadioButton.h"
#include "GuiManager.h"

namespace sgl
{
	RadioButton::RadioButton()
		:Window()
		,label_()
	{
	}

	RadioButton::RadioButton(Window* parent, const std::string& label)
		:Window(parent)
		,label_(label)
		,is_checked_(false)
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
			auto box_size = 12;
			auto label_offset = 8 + box_size;
			auto color_theme = manager_->getStyleManager().getColorTheme();
			auto circle_center_x = screen_pos_x_ + box_size / 2;
			auto circle_center_y = screen_pos_y_ + box_size / 2;
			auto circle_radius = box_size / 2;

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
				// draw label next to check box
				renderTextAtPos(renderer, label_, screen_pos_x_ + label_offset, screen_pos_y_ + circle_radius, PosAlign::Left, color_theme.text_active, color_theme.text_background);
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
		/*auto evhandler = eventhandlers_.find(eventtype::button);
		if (evhandler != std::end(eventhandlers_))
		{
			event e;
			e.type = eventtype::button;
			evhandler->second(e);
		}*/
	}
}