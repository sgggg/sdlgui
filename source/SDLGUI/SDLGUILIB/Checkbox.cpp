#include "stdafx.h"
#include "Checkbox.h"
#include "GuiManager.h"

namespace sgl
{
	Checkbox::Checkbox() :
		Window(),
		label_(),
		is_checked_(false)
	{
	}

	Checkbox::Checkbox(Window* parent, const std::string& label) :
		Window(parent),
		label_(label),
		is_checked_(false)
	{
	}

	std::string Checkbox::getLabel() const
	{
		return label_;
	}

	void Checkbox::setLabel(const std::string& text)
	{
		label_ = text;
	}

	bool Checkbox::isChecked() const
	{
		return is_checked_;
	}

	void Checkbox::setChecked(bool is_checked)
	{
		is_checked_ = is_checked;
	}

	void Checkbox::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			const auto& window_style = manager_->getStyleManager().getWindowStyle();
			const auto box_size = window_style.checkbox_size;
			const auto label_offset = window_style.inner_padding + box_size;

			if (is_active_)
			{
				// draw box
				if (contains_mouse_)
				{
					drawFilledRectangle(renderer, screen_pos_.x, screen_pos_.y, box_size, box_size, color_theme.control_contains_mouse);
				}
				else
				{
					drawFilledRectangle(renderer, screen_pos_.x, screen_pos_.y, box_size, box_size, color_theme.control_background_active);
				}
				drawRectangle(renderer, screen_pos_.x, screen_pos_.y, box_size, box_size, color_theme.control_frame_active);
				if (is_checked_)
				{
					drawFilledRectangle(renderer, screen_pos_.x + 2, screen_pos_.y + 2, box_size - 4, box_size - 4, color_theme.control_frame_active);
				}
				else
				{
					// draw in unchecked state -> no fill
				}
				// draw label next to control
				renderTextAtPos(renderer, label_, screen_pos_.x + label_offset, screen_pos_.y + box_size / 2, Alignment::Left, color_theme.text_active, color_theme.text_background);
			}
			else
			{
				// TODO draw in inactive state (grayed out)
			}
		}
	}

	void Checkbox::triggerClicked()
	{
		is_checked_ = !is_checked_;
		const auto event_type = is_checked_ ? EventType::CheckBoxChecked : EventType::CheckBoxUnchecked;
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
