#include "stdafx.h"
#include "Button.h"
#include "GuiManager.h"

namespace sgl
{
	Button::Button()
		:Window()
		,label_()
	{
	}

	Button::Button(Window* parent, const std::string& label)
		:Window(parent)
		,label_(label)
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

	void Button::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			auto colorTheme = manager_->getStyleManager().getColorTheme();
			SDL_Color colorButtonFill, colorButtonFrame, colorButtonLabel;
			if (isActive_)
			{
				if (isClicked_)
				{
					// draw button in pressed state
					colorButtonFill = colorTheme.controlPressed;
				}
				else if (containsMouse_)
				{
					// draw button in mouse-over state
					colorButtonFill = colorTheme.controlContainsMouse;
				}
				else
				{
					// draw button in normal state (not pressed, not mouse-over)
					colorButtonFill = colorTheme.controlBackgroundActive;
				}
				colorButtonFrame = colorTheme.controlFrameActive;
				colorButtonLabel = colorTheme.textActive;
			}
			else
			{
				colorButtonFill = colorTheme.controlBackgroundInactive;
				colorButtonFrame = colorTheme.controlFrameInactive;
				colorButtonLabel = colorTheme.textInactive;
			}
			// draw button fill color
			drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorButtonFill);
			// draw outline
			SDL_Rect outlineRect = { screenPosX_, screenPosY_, width_, height_ };
			drawRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorButtonFrame);
			// draw button label
			auto buttonCenter = getCenter({ screenPosX_, screenPosY_, width_, height_ });
			renderTextAtPos(renderer, label_, buttonCenter.x, buttonCenter.y, PosAlign::Center, colorButtonLabel, colorTheme.textBackground);
		}
	}

	void Button::triggerClicked()
	{
		auto evHandler = eventHandlers_.find(EventType::ButtonPressed);
		if (evHandler != std::end(eventHandlers_))
		{
			Event e;
			e.type_ = EventType::ButtonPressed;
			e.time_ = manager_->getApplicationTime();
			evHandler->second(e);
		}
	}
}