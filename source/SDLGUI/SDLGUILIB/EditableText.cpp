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
		addCharacter(cursor_position_, static_cast<char>(keycode));
	}
	else
	{
		switch (keycode)
		{
		case SDLK_BACKSPACE:
			if (!current_text_.empty())
			{
				// if text is selected, remove selected text
				if (selection_start_ != -1)
				{
					// remove the selected characters
					auto markers = std::minmax(cursor_position_, selection_start_);
					removeCharacterRange(markers.first, markers.second);
				}
				else if (cursor_position_ > 0)
				{
					// remove the character to the _left_ of the current cursor position
					removeCharacterRange(cursor_position_ - 1, cursor_position_);
				}
			}
			break;
		case SDLK_DELETE:
			if (!current_text_.empty())
			{
				// if text is selected, remove selected text
				if (selection_start_ != -1)
				{
					// remove the selected characters
					auto markers = std::minmax(cursor_position_, selection_start_);
					removeCharacterRange(markers.first, markers.second);
				}
				else if (cursor_position_ < current_text_.size())
				{
					// remove the character to the _right_ of the current cursor position
					removeCharacterRange(cursor_position_, cursor_position_ + 1);
				}
			}
			break;
		case SDLK_RIGHT:
			if (current_text_.size() > cursor_position_)
			{
				++cursor_position_;
			}
			break;
		case SDLK_LEFT:
			if (cursor_position_ > 0)
			{
				--cursor_position_;
			}
			break;
		default:
			// auto keyname = SDL_GetKeyName(keycode);
			// std::cout << "key " << keyname << " not handled" << std::endl;
			break;
		}
	}
	std::cout << "DEBUG: cursor position: " << cursor_position_ << std::endl;
}

std::string sgl::internals::EditableText::getText() const
{
	return firstPart_ + selection_ + lastPart_;
}

*/