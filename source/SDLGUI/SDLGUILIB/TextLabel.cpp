#include "stdafx.h"
#include "TextLabel.h"

namespace sgl
{
	TextLabel::TextLabel()
		:Window()
	{
	}

	TextLabel::TextLabel(Window* parent, const std::string& text)
		:Window(parent, text)
	{
	}

	void TextLabel::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			if (isActive_)
			{
				// TODO draw text
			}
			else
			{
				// TODO draw inactive text (grayed out)
			}
		}
	}
}
