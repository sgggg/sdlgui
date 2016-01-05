#include "stdafx.h"
#include "Button.h"
#include "Gui.h"

namespace sgl
{
	Button::Button()
		:Window()
	{
	}

	Button::Button(Window* parent, const std::string& label)
		:Window(parent, label)
	{
	}

	void Button::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			if (isActive_)
			{
				auto colorTheme = guiRoot_->getStyleManager().getColorTheme();
				if (isClicked_)
				{
					// draw button in pressed state
					drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlPressed);
				}
				else if (containsMouse_)
				{
					// draw button in mouse-over state
					drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlContainsMouse);
				}
				else
				{
					// draw button in normal state (not pressed, not mouse-over)
					drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlBackgroundActive);
				}
				// always draw the same outline
				SDL_Rect outlineRect = { screenPosX_, screenPosY_, width_, height_ };
				drawRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlFrameActive);

				// render text
				renderTextAtPos(renderer, label_, screenPosX_, screenPosY_, colorTheme.textActive, colorTheme.textBackground);
			}
			else
			{
				// TODO draw button in inactive state (grayed out)
			}
		}
	}

	void Button::triggerClicked()
	{
		auto evHandler = eventHandlers_.find(EventType::Button);
		if (evHandler != std::end(eventHandlers_))
		{
			Event e;
			e.type = EventType::Button;
			evHandler->second(e);
		}
	}

	void Button::triggerDoubleClicked()
	{
		// do nothing
	}

	void Button::triggerMouseEntered()
	{
		//std::cout << "Button " << label_ << ": mouse entered" << std::endl;
	}

	void Button::triggerMouseLeft()
	{
		//std::cout << "Button " << label_ << ": mouse left" << std::endl;
	}

	void Button::triggerMouseDown()
	{
		//std::cout << "Window " << label_ << ": mouse down" << std::endl;
	}

	void Button::triggerMouseUp()
	{
		//std::cout << "Window " << label_ << ": mouse up" << std::endl;
	}
}