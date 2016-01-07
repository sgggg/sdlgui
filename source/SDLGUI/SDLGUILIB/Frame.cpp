#include "stdafx.h"
#include "Frame.h"
#include "Gui.h"

namespace sgl
{
	Frame::Frame()
		:Window()
		,title_()
		,hasTitleBar_(false)
	{
	}

	Frame::Frame(Window* parent, const std::string& title)
		:Window(parent)
		,title_(title)
		,hasTitleBar_(false)
	{
	}

	void Frame::setTitleBarVisible(bool isTitleBarVisible)
	{
		hasTitleBar_ = isTitleBarVisible;
	}

	bool Frame::hasTitleBar() const
	{
		return hasTitleBar_;
	}

	void Frame::draw(SDL_Renderer * renderer)
	{
		Window::draw(renderer);
		if (isVisible_)
		{
			auto colorTheme = guiRoot_->getStyleManager().getColorTheme();
			if (hasTitleBar_)
			{
				auto titleBarHeight = 16;
				auto titleBarMargin = 2;
				auto titleBarTextOffset = 8;
				SDL_Rect titleBarArea = { screenPosX_ + titleBarMargin, screenPosY_ + titleBarMargin, width_ - 2 * titleBarMargin, titleBarHeight };
				drawFilledRectangle(renderer, titleBarArea.x, titleBarArea.y, titleBarArea.w, titleBarArea.h, colorTheme.windowTitlebar);
				renderTextAtPos(renderer, title_, titleBarArea.x + titleBarTextOffset, titleBarArea.y + titleBarHeight / 2,
					PosAlign::Left, colorTheme.textActive, colorTheme.textBackground);
			}
		}
	}
}
