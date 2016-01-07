#include "stdafx.h"
#include "TextInput.h"
#include "Gui.h"

namespace sgl
{
	TextInput::TextInput()
		:Window()
		,defaultText_()
		,currentText_()
	{
	}

	TextInput::TextInput(Window* parent, const std::string& defaultText)
		:Window(parent)
		,defaultText_(defaultText)
		,currentText_(defaultText)
	{
	}

	std::string TextInput::getText() const
	{
		return currentText_;
	}

	void TextInput::setText(const std::string & newText)
	{
		currentText_ = newText;
	}

	void TextInput::draw(SDL_Renderer* renderer)
	{
		if (isVisible_) 
		{
			if (isActive_)
			{
				auto colorTheme = guiRoot_->getStyleManager().getColorTheme();
				if (containsMouse_)
				{
					// do nothing
				}
				else
				{
					//nothing
				}
				// draw TextInput in normal state (not pressed, not mouse-over)
				drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlInputBackground);
				// always draw the same outline
				SDL_Rect outlineRect = { screenPosX_, screenPosY_, width_, height_ };
				drawRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlFrameActive);

				//TODO render text

				//TODO input a curser when area is clicked (remove it when clicking some place else)

				//TODO add keyboard as input

				//(optional) add written and submitted text to another area
				
			}

		}
	}


}