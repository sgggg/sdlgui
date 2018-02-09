#include "stdafx.h"
#include "Button.h"
#include "GuiManager.h"

namespace sgl
{
	Button::Button() :
		Window(),
		label_(),
		label_alignment_(Alignment::Center)
	{
	}

	Button::Button(Window* parent, const std::string& label) :
		Window(parent),
		label_(label),
		label_alignment_(Alignment::Center)
	{
	}

	std::string Button::getLabel() const
	{
		return label_;
	}

	void Button::setLabel(const std::string& text)
	{
		label_ = text;
	}

	Alignment Button::getLabelAlignment() const
	{
		return label_alignment_;
	}

	void Button::setLabelAlignment(Alignment alignment)
	{
		label_alignment_ = alignment;
	}

	void Button::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			SDL_Color color_button_fill, color_button_frame, color_button_label;
			if (is_active_)
			{
				if (is_clicked_)
				{
					// draw button in pressed state
					color_button_fill = color_theme.control_pressed;
				}
				else if (contains_mouse_)
				{
					// draw button in mouse-over state
					color_button_fill = color_theme.control_contains_mouse;
				}
				else
				{
					// draw button in normal state (not pressed, not mouse-over)
					color_button_fill = color_theme.control_background_active;
				}
				color_button_frame = color_theme.control_frame_active;
				color_button_label = color_theme.text_active;
			}
			else
			{
				color_button_fill = color_theme.control_background_inactive;
				color_button_frame = color_theme.control_frame_inactive;
				color_button_label = color_theme.text_inactive;
			}
			// draw button fill color
			drawFilledRectangle(renderer, screen_pos_.x, screen_pos_.y, size_.width, size_.height, color_button_fill);
			// draw outline
			drawRectangle(renderer, screen_pos_.x, screen_pos_.y, size_.width, size_.height, color_button_frame);
			// draw button label
			const auto aligned_point = getAlignedPointInRect({ screen_pos_.x, screen_pos_.y, size_.width, size_.height }, label_alignment_);
			renderTextAtPos(renderer, label_, aligned_point.x, aligned_point.y, label_alignment_, color_button_label, color_theme.text_background);
		}
	}

	void Button::triggerClicked()
	{
		sendEvent(EventType::ButtonPressed);
	}

	void Button::triggerMouseDown()
	{
		sendEvent(EventType::ButtonDown);
	}

	void Button::triggerMouseUp()
	{
		sendEvent(EventType::ButtonUp);
	}

	void Button::sendEvent(EventType event_type)
	{
		Event e;
		e.type_ = event_type;
		e.time_ = manager_->getApplicationTime();
		callEventCallback(e);
	}
}

