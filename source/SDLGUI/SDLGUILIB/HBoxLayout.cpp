#include "stdafx.h"
#include "HBoxLayout.h"

namespace sgl
{
	HBoxLayout::HBoxLayout()
		: Window()
	{
		hasTitleBar_ = false;
	}

	HBoxLayout::HBoxLayout(Window* parentWindow, const std::string& label)
		: Window(parentWindow, label)
	{
		hasTitleBar_ = false;
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
}