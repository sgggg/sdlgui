#include "stdafx.h"
#include "TextInput.h"
#include "GuiManager.h"

namespace sgl
{
	TextInput::TextInput()
		:Window()
		,default_text_()
		,current_text_()
		,cursor_position_(0)
		,selection_start_(-1)
	{
	}

	TextInput::TextInput(Window* parent, const std::string& default_text)
		:Window(parent)
		,default_text_(default_text)
		,current_text_()
		,cursor_position_(0)
		,selection_start_(-1)
	{
	}

	std::string TextInput::getText() const
	{
		return current_text_;
	}

	void TextInput::setText(const std::string& new_text)
	{
		current_text_ = new_text;
	}
	
	void TextInput::draw(SDL_Renderer* renderer)
	{
		if (is_visible_) 
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			const auto& window_style = manager_->getStyleManager().getWindowStyle();
			SDL_Color color_input_fill, colorInputFrame, colorInputText;
			auto outline_rect = SDL_Rect{ screen_pos_x_, screen_pos_y_, width_, height_ };
			if (is_active_)
			{
				drawFilledRectangle(renderer, screen_pos_x_, screen_pos_y_, width_, height_, color_theme.control_text_area_background);
				drawRectangle(renderer, screen_pos_x_, screen_pos_y_, width_, height_, color_theme.control_frame_active);
				auto cursor_pos_x = screen_pos_x_ + window_style.inner_padding;
				// render text, stored in current_text_
				if (current_text_.empty())
				{
					// render default text
					//renderTextAtPos(renderer, default_text_, screen_pos_x_ + window_style.inner_padding, screen_pos_y_ + height_ / 2, PosAlign::Left, color_theme.text_default, color_theme.text_background);
				}
				else
				{
					// render current text in two parts, the part to the left of the cursor, and the part to the right
					// then draw the cursor in between
					auto first_string = current_text_.substr(0, cursor_position_);
					auto last_string = current_text_.substr(cursor_position_);
					if (!first_string.empty())
					{
						auto first_string_surface = renderTextToSurface(first_string, color_theme.text_active);
						cursor_pos_x += first_string_surface->w;
						renderAndFreeSurface(renderer, first_string_surface, screen_pos_x_ + window_style.inner_padding, screen_pos_y_ + height_ / 2, PosAlign::Left);
					}
					if (!last_string.empty())
					{
						auto last_string_surface = renderTextToSurface(last_string, color_theme.text_active);
						renderAndFreeSurface(renderer, last_string_surface, cursor_pos_x, screen_pos_y_ + height_ / 2, PosAlign::Left);
					}
				}
				if (hasFocus())
				{
					if (manager_->getApplicationTime().count() % 1000 < 500)
					{
						drawCursor(renderer, cursor_pos_x);
					}
				}
			}
			else
			{
				drawFilledRectangle(renderer, screen_pos_x_, screen_pos_y_, width_, height_, color_theme.control_background_inactive);
				drawRectangle(renderer, screen_pos_x_, screen_pos_y_, width_, height_, color_theme.control_frame_inactive);
				renderTextAtPos(renderer, default_text_, screen_pos_x_ + window_style.inner_padding, screen_pos_y_ + height_ / 2, PosAlign::Left, color_theme.text_inactive, color_theme.text_background);
			}
		}
	}

	void TextInput::triggerKeyDown(SDL_Keysym key)
	{
		auto keycode = key.sym;
		if (keycode >= 32 && keycode <= 122)
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

	void TextInput::drawCursor(SDL_Renderer* renderer, int relative_x)
	{
		const auto& color_theme = manager_->getStyleManager().getColorTheme();
		const auto& window_style = manager_->getStyleManager().getWindowStyle();
		// draw cursor inside text box at the appropriate position 
		// and with the correct height (depending on font size)
		SDL_SetRenderDrawColor(renderer, color_theme.control_input_cursor.r, color_theme.control_input_cursor.g,
			color_theme.control_input_cursor.b, color_theme.control_input_cursor.a);
		auto cursor_start	= Point{ relative_x, screen_pos_y_ + (height_ / 2) - (window_style.font_size / 2) };
		auto cursor_end		= Point{ relative_x, cursor_start.y + window_style.font_size };
		SDL_RenderDrawLine(renderer, cursor_start.x, cursor_start.y, cursor_end.x, cursor_end.y);
	}

	void TextInput::removeCharacterRange(int left_index, int right_index)
	{
		// remove the selected characters
		auto left_str = current_text_.substr(0, left_index);
		auto right_str = current_text_.substr(right_index);
		current_text_ = left_str + right_str;
		cursor_position_ = left_index;
	}

	void TextInput::addCharacterRange(int index, const std::string& characters)
	{
		// insert given characters at specified position
		auto left_str = current_text_.substr(0, index);
		auto right_str = current_text_.substr(index);
		current_text_ = left_str + characters + right_str;
		cursor_position_ = left_str.size() + characters.size();
	}

	void TextInput::addCharacter(int index, char character)
	{
		if (index == current_text_.size())
		{
			current_text_.push_back(character);
		}
		else
		{
			auto left_str = current_text_.substr(0, index);
			auto right_str = current_text_.substr(index);
			current_text_ = left_str + character + right_str;
		}
		++cursor_position_;
	}
}
