#include "stdafx.h"
#include "Button.h"

namespace sgl
{
	Button::Button()
		:Window()
	{
	}

	Button::Button(Window* parent, const std::string& label)
		:Window(parent, label)
	{
		parent->addChild(*this);
	}

	void Button::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			SDL_Rect outlineRect = { screenPosX_, screenPosY_, width_, height_ }; //draw gray outline
			SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
			SDL_RenderDrawRect(renderer, &outlineRect);

			renderTextAtPos(renderer, label_, screenPosX_, screenPosY_, { 0,0,0 }, { 0xC0, 0xC0, 0xC0 });
			if (isActive_)
			{
				if (isClicked_)
				{
					// TODO draw button in pressed state
				}
				else if (containsMouse_)
				{
					// TODO draw button in mouse-over state
				}
				else
				{
					// TODO draw button in normal state (not pressed, not mouse-over)
				}
				// TODO draw button label
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