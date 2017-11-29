#include "stdafx.h"
#include "HBoxLayout.h"

namespace sgl
{
	HBoxLayout::HBoxLayout()
		:Window()
	{
	}

	HBoxLayout::HBoxLayout(Window* parent_window)
		:Window(parent_window)
	{
	}

	void HBoxLayout::setHorizontalPadding(int d)
	{
		horizontal_padding_ = d;
	}

	void HBoxLayout::setMarginTop(int t)
	{
		margin_top_ = t;
	}

	void HBoxLayout::setMarginBottom(int b)
	{
		margin_bottom_ = b;
	}

	void HBoxLayout::updateLayout()
	{
		const auto width_per_child = size_.width / children_.size();
		auto i = 0;
		for (auto child : children_)
		{
			child->setSize(width_per_child - 2 * horizontal_padding_, size_.height - margin_top_ - margin_bottom_);
			child->setPosition(i * width_per_child + horizontal_padding_, 0);
			i++;
		}
	}

	void HBoxLayout::draw(SDL_Renderer* renderer)
	{
		// draw all windows inside the layout
		for (const auto& child : children_)
		{
			child->draw(renderer);
		}
	}
}