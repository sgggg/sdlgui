#include "stdafx.h"
#include "Frame.h"
#include "GuiManager.h"

namespace sgl
{
	Frame::Frame(Window* parent, const std::string& title)
		:Window(parent)
		,title_(title)
		,has_title_bar_(false)
	{
	}

	void Frame::setTitleBar(bool is_title_bar_visible)
	{
		has_title_bar_ = is_title_bar_visible;
	}

	bool Frame::hasTitleBar() const
	{
		return has_title_bar_;
	}

	void Frame::setTitle(const std::string& title)
	{
		title_ = title;
	}

	std::string Frame::getTitle() const 
	{
		return title_;
	}

	void Frame::draw(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			const auto& color_theme = manager_->getStyleManager().getColorTheme();
			// draw this window
			if (is_active_)
			{
				drawFilledRectangle(renderer, screen_pos_x_, screen_pos_y_, width_, height_, color_theme.window_background);
				drawRectangle(renderer, screen_pos_x_, screen_pos_y_, width_, height_, color_theme.window_frame_focus);
				if (has_title_bar_)
				{
					auto title_bar_height = 16;
					auto title_bar_margin = 2;
					auto title_bar_text_offset = 8;
					auto title_bar_area = SDL_Rect{ screen_pos_x_ + title_bar_margin, screen_pos_y_ + title_bar_margin, width_ - 2 * title_bar_margin, title_bar_height };
					drawFilledRectangle(renderer, title_bar_area.x, title_bar_area.y, title_bar_area.w, title_bar_area.h, color_theme.window_titlebar);
					renderTextAtPos(renderer, title_, title_bar_area.x + title_bar_text_offset, title_bar_area.y + title_bar_height / 2,
						PosAlign::Left, color_theme.text_active, color_theme.text_background);
				}
			}
			else
			{
				drawFilledRectangle(renderer, screen_pos_x_, screen_pos_y_, width_, height_, color_theme.window_background);
			}

			// draw children
			for (const auto& child : children_)
			{
				child->draw(renderer);
			}
		}
	}
}
