#include "stdafx.h"
#include "HBoxLayout.h"

namespace sgl
{
	HBoxLayout::HBoxLayout()
		:Window()
	{
	}

	HBoxLayout::HBoxLayout(Window* parentWindow)
		:Window(parentWindow)
	{
	}

	void HBoxLayout::setHorizontalPadding(int d)
	{
		horizontalPadding_ = d;
	}

	void HBoxLayout::setMarginTop(int t)
	{
		marginTop_ = t;
	}

	void HBoxLayout::setMarginBottom(int b)
	{
		marginBottom_ = b;
	}

	void HBoxLayout::updateLayout()
	{
		auto widthPerChild = width_ / children_.size();
		auto i = 0;
		for (auto child : children_)
		{
			child->setSize( widthPerChild - 2*horizontalPadding_, height_ - marginTop_ - marginBottom_);
			child->setPosition(i*widthPerChild + horizontalPadding_, 0);
			i++;
		}
	}

	void HBoxLayout::draw(SDL_Renderer * renderer)
	{
		// draw all windows inside the layout
		for (const auto& child : children_)
		{
			child->draw(renderer);
		}
	}
}