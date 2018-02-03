#include "stdafx.h"
#include "RadioButton.h"
#include "GuiManager.h"

namespace sgl
{
	RadioButton::RadioButton() :
		Window(),
		label_(),
		is_checked_(false)
	{
	}

	RadioButton::RadioButton(Window* parent, const std::string& label) :
		Window(parent),
		label_(label),
		is_checked_(false)
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
		auto was_checked = is_checked_;
		is_checked_ = is_checked;
		if (hasChangedToChecked(was_checked))
		{
			uncheckSiblingRadioButtons();
		}
	}

	bool RadioButton::hasChangedToChecked(bool was_checked)
	{
		return is_checked_ && (is_checked_ != was_checked);
	}

	void RadioButton::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			constexpr auto box_size = 12;
			constexpr auto label_offset = 8 + box_size;
			const auto circle_center = Point{ screen_pos_.x + box_size / 2, screen_pos_.y + box_size / 2 };
			const auto circle_radius = box_size / 2;

			if (is_active_)
			{
				drawActiveState(renderer, circle_center, circle_radius, label_offset);
			}
			else
			{
				// TODO draw in inactive state (grayed out)
			}
		}
	}

	void RadioButton::drawActiveState(SDL_Renderer * renderer, const sgl::Point &circle_center, const int &circle_radius, const int &label_offset)
	{
		const auto& color_theme = manager_->getStyleManager().getColorTheme();
		if (contains_mouse_)
		{
			drawFilledCircle(renderer, circle_center.x, circle_center.y, circle_radius, color_theme.control_contains_mouse);
		}
		else
		{
			drawFilledCircle(renderer, circle_center.x, circle_center.y, circle_radius, color_theme.control_background_active);
		}
		drawCircle(renderer, circle_center.x, circle_center.y, circle_radius, color_theme.control_frame_active);
		if (is_checked_)
		{
			drawFilledCircle(renderer, circle_center.x, circle_center.y, circle_radius - 2, color_theme.control_frame_active);
		}
		renderTextAtPos(renderer, label_, screen_pos_.x + label_offset, screen_pos_.y + circle_radius, Alignment::Left, color_theme.text_active, color_theme.text_background);
	}

	void RadioButton::triggerClicked()
	{
		auto was_checked = is_checked_;
		is_checked_ = true;
		if (hasChangedToChecked(was_checked))
		{
			uncheckSiblingRadioButtons();
		}

		sendCheckedEvent();
	}

	void RadioButton::sendCheckedEvent()
	{
		const auto event_type = is_checked_ ? EventType::Checked : EventType::Unchecked;
		Event e;
		e.type_ = event_type;
		e.time_ = manager_->getApplicationTime();
		callEventCallback(e);
	}

	void RadioButton::uncheckSiblingRadioButtons()
	{
		if (parent_ != nullptr)
		{
			for (auto sibling : parent_->getChildren())
			{
				if (sibling != this)
				{
					auto sibling_radio_button = dynamic_cast<RadioButton*>(sibling);
					if (sibling_radio_button)
					{
						sibling_radio_button->is_checked_ = false;
						// TODO sibling doesn't send the necessary Unchecked event
					}
				}
			}
		}
	}
}
