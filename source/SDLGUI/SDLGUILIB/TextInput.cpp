#include "stdafx.h"
#include "TextInput.h"
#include "GuiManager.h"

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
			auto colorTheme = manager_->getStyleManager().getColorTheme();
			auto windowStyle = manager_->getStyleManager().getWindowStyle();
			SDL_Color colorInputFill, colorInputFrame, colorInputText;
			SDL_Rect outlineRect = { screenPosX_, screenPosY_, width_, height_ };
			if (isActive_)
			{
				drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlTextAreaBackground);
				drawRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlFrameActive);
				if (hasFocus())
				{
					if (manager_->getApplicationTime() % 1000 < 500)
					{
						// draw cursor inside text box at the appropriate position 
						// and with the correct height (depending on font size)
						SDL_SetRenderDrawColor(renderer, colorTheme.controlInputCursor.r, colorTheme.controlInputCursor.g, 
							colorTheme.controlInputCursor.b, colorTheme.controlInputCursor.a);
						Point cursorStart	= { relativePosX_ + 2, relativePosY_ + 2 };
						Point cursorEnd		= { cursorStart.x, cursorStart.y + windowStyle.fontSize };
						SDL_RenderDrawLine(renderer, cursorStart.x, cursorStart.y, cursorEnd.x, cursorEnd.y);
					}
				}
				// render text, stored in currentText_
				// TODO use color for active text
			}
			else
			{
				drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlBackgroundInactive);
				drawRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlFrameInactive);
				// render text, stored in currentText_
				// TODO use color for inactive text

			}
		}
	}


}