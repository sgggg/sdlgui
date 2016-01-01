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
}