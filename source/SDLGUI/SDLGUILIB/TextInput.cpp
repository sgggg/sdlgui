#include "stdafx.h"
#include "TextInput.h"
#include "GuiManager.h"

namespace sgl
{
	TextInput::TextInput()
		:Window()
		,defaultText_()
		,currentText_()
		,cursorPosition_(0)
		,selectionStart_(-1)
	{
	}

	TextInput::TextInput(Window* parent, const std::string& defaultText)
		:Window(parent)
		,defaultText_(defaultText)
		,currentText_()
		,cursorPosition_(0)
		,selectionStart_(-1)
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
				auto cursorPosX = screenPosX_ + windowStyle.innerPadding;
				// render text, stored in currentText_
				if (currentText_.empty())
				{
					// render default text
					renderTextAtPos(renderer, defaultText_, screenPosX_ + windowStyle.innerPadding, screenPosY_ + height_ / 2, PosAlign::Left, colorTheme.textDefault, colorTheme.textBackground);
				}
				else
				{
					// render current text in two parts, the part to the left of the cursor, and the part to the right
					// then draw the cursor in between
					auto firstString = currentText_.substr(0, cursorPosition_);
					auto lastString = currentText_.substr(cursorPosition_);
					if (!firstString.empty())
					{
						auto firstStrSurface = renderTextToSurface(firstString, colorTheme.textActive);
						cursorPosX += firstStrSurface->w;
						renderAndFreeSurface(renderer, firstStrSurface, screenPosX_ + windowStyle.innerPadding, screenPosY_ + height_ / 2, PosAlign::Left);
					}
					if (!lastString.empty())
					{
						auto lastStrSurface = renderTextToSurface(lastString, colorTheme.textActive);
						renderAndFreeSurface(renderer, lastStrSurface, cursorPosX, screenPosY_ + height_ / 2, PosAlign::Left);
					}
				}
				if (hasFocus())
				{
					if (manager_->getApplicationTime() % 1000 < 500)
					{
						drawCursor(renderer, cursorPosX);
					}
				}
			}
			else
			{
				drawFilledRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlBackgroundInactive);
				drawRectangle(renderer, screenPosX_, screenPosY_, width_, height_, colorTheme.controlFrameInactive);
				renderTextAtPos(renderer, defaultText_, screenPosX_ + windowStyle.innerPadding, screenPosY_ + height_ / 2, PosAlign::Left, colorTheme.textInactive, colorTheme.textBackground);
			}
		}
	}

	void TextInput::triggerKeyDown(SDL_Keycode keycode)
	{
		if (keycode >= 91 && keycode <= 122 ||
			keycode >= 32 && keycode <= 64)
		{
			// these are the printable characters
			addCharacter(cursorPosition_, static_cast<char>(keycode));
		}
		else
		{
			switch (keycode)
			{
			case SDLK_BACKSPACE:
				if (!currentText_.empty())
				{
					// if text is selected, remove selected text
					if (selectionStart_ != -1)
					{
						// remove the selected characters
						auto markers = std::minmax(cursorPosition_, selectionStart_);
						removeCharacterRange(markers.first, markers.second);
					}
					else if (cursorPosition_ > 0)
					{
						// remove the character to the _left_ of the current cursor position
						removeCharacterRange(cursorPosition_ - 1, cursorPosition_);
					}
				}
				break;
			case SDLK_DELETE:
				if (!currentText_.empty())
				{
					// if text is selected, remove selected text
					if (selectionStart_ != -1)
					{
						// remove the selected characters
						auto markers = std::minmax(cursorPosition_, selectionStart_);
						removeCharacterRange(markers.first, markers.second);
					}
					else if (cursorPosition_ < currentText_.size())
					{
						// remove the character to the _right_ of the current cursor position
						removeCharacterRange(cursorPosition_, cursorPosition_ + 1);
					}
				}
				break;
			case SDLK_RIGHT:
				if (currentText_.size() > cursorPosition_)
				{
					++cursorPosition_;
				}
				break;
			case SDLK_LEFT:
				if (cursorPosition_ > 0)
				{
					--cursorPosition_;
				}
				break;
			default:
				// auto keyname = SDL_GetKeyName(keycode);
				// std::cout << "key " << keyname << " not handled" << std::endl;
				break;
			}
		}
		std::cout << "DEBUG: cursor position: " << cursorPosition_ << std::endl;
	}

	void TextInput::drawCursor(SDL_Renderer* renderer, int relativeX)
	{
		auto colorTheme = manager_->getStyleManager().getColorTheme();
		auto windowStyle = manager_->getStyleManager().getWindowStyle();
		// draw cursor inside text box at the appropriate position 
		// and with the correct height (depending on font size)
		SDL_SetRenderDrawColor(renderer, colorTheme.controlInputCursor.r, colorTheme.controlInputCursor.g,
			colorTheme.controlInputCursor.b, colorTheme.controlInputCursor.a);
		Point cursorStart	= { relativeX, screenPosY_ + (height_ / 2) - (windowStyle.fontSize / 2) };
		Point cursorEnd		= { relativeX, cursorStart.y + windowStyle.fontSize };
		SDL_RenderDrawLine(renderer, cursorStart.x, cursorStart.y, cursorEnd.x, cursorEnd.y);
	}

	void TextInput::removeCharacterRange(int leftIndex, int rightIndex)
	{
		// remove the selected characters
		auto leftStr = currentText_.substr(0, leftIndex);
		auto rightStr = currentText_.substr(rightIndex);
		currentText_ = leftStr + rightStr;
		cursorPosition_ = leftIndex;
	}

	void TextInput::addCharacterRange(int index, const std::string& characters)
	{
		// insert given characters at specified position
		auto leftStr = currentText_.substr(0, index);
		auto rightStr = currentText_.substr(index);
		currentText_ = leftStr + characters + rightStr;
		cursorPosition_ = leftStr.size() + characters.size();
	}

	void TextInput::addCharacter(int index, char character)
	{
		if (index == currentText_.size())
		{
			currentText_.push_back(character);
		}
		else
		{
			auto leftStr = currentText_.substr(0, index);
			auto rightStr = currentText_.substr(index);
			currentText_ = leftStr + character + rightStr;
		}
		++cursorPosition_;
	}
}
