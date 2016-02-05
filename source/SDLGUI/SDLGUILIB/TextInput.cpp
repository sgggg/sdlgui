#include "stdafx.h"
#include "TextInput.h"
#include "GuiManager.h"

namespace sgl
{
	TextInput::TextInput()
		:Window()
		,defaultText_()
		,currentText_()
		,curserPosition_(0)
	{
	}

	TextInput::TextInput(Window* parent, const std::string& defaultText)
		:Window(parent)
		,defaultText_(defaultText)
		,currentText_()
		,curserPosition_(0)
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
			auto margin = 2;	// TODO load from config
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
						Point cursorStart	= { screenPosX_ + margin, screenPosY_ + (height_ / 2) - (windowStyle.fontSize / 2) };
						Point cursorEnd		= { cursorStart.x, cursorStart.y + windowStyle.fontSize };
						SDL_RenderDrawLine(renderer, cursorStart.x, cursorStart.y, cursorEnd.x, cursorEnd.y);
					}
				}
				// render text, stored in currentText_
				if (currentText_.empty())
				{
					// render default text
					renderTextAtPos(renderer, defaultText_, screenPosX_ + margin, screenPosY_ + height_ / 2, PosAlign::Left, colorTheme.textDefault, colorTheme.textBackground);
				}
				else
				{
					// render entered text
					renderTextAtPos(renderer, currentText_, screenPosX_ + margin, screenPosY_ + height_ / 2, PosAlign::Left, colorTheme.textActive, colorTheme.textBackground);
				}
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

	void TextInput::triggerKeyDown(SDL_Keycode keycode)
	{
		if (keycode >= 97 && keycode <= 122)
		{
			// these are the printable characters
			currentText_ += static_cast<char>(keycode);
		}
		else
		{
			switch (keycode)
			{
			case SDLK_BACKSPACE:
				if (!currentText_.empty())
				{
					currentText_.pop_back();
				}
				break;
				// TODO add other non-printable key logic (DELETE, etc.)
			default:
				// do nothing
				auto keyname = SDL_GetKeyName(keycode);
				std::cout << "key " << keyname << " not handled" << std::endl;
				break;
			}
		}
	}
}
