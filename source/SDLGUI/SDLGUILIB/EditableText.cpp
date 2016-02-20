#include "stdafx.h"
#include "EditableText.h"
/*
sgl::internals::EditableText::EditableText(const std::string & text)
	:firstPart_()
	,selection_()
	,lastPart_()
{
}

void sgl::internals::EditableText::processKeyPress(SDL_Keysym key)
{
	auto keycode = key.sym;
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

std::string sgl::internals::EditableText::getText() const
{
	return firstPart_ + selection_ + lastPart_;
}

*/