#include "stdafx.h"
#include "GridLayout.h"
#include <assert.h>
#include <algorithm>

namespace sgl
{
	GridLayout::GridLayout()
		:Window()
	{
	}

	GridLayout::GridLayout(Window* parentWindow)
		: Window(parentWindow)
	{
	}

	void GridLayout::setPadding(int top, int bottom, int left, int right)
	{
		paddingTop_ = top;
		paddingBottom_ = bottom;
		paddingLeft_ = left;
		paddingRight_ = right;
	}

	void GridLayout::setMargin(int top, int bottom, int left, int right)
	{
		marginTop_ = top;
		marginBottom_ = bottom;
		marginLeft_ = left;
		marginRight_ = right;
	}

	void GridLayout::updateLayout()
	{
		auto widthPerCell = (width_ - marginLeft_ - marginRight_) / (maxH_ + 1);	//use (maxH_+1) because positioning starts at index 0
		auto heightPerCell = (height_ - marginTop_ - marginBottom_) / (maxV_ + 1);
		auto widthPerChild = widthPerCell - paddingLeft_ - paddingRight_;
		auto heightPerChild = heightPerCell - paddingTop_ - paddingBottom_;
		for (auto gridElem : grid_)
		{
			gridElem.first->setSize(widthPerChild, heightPerChild);
			gridElem.first->setPosition( marginLeft_ + gridElem.second.h * widthPerCell  + paddingLeft_,
										 marginTop_  + gridElem.second.v * heightPerCell + paddingTop_ );
		}
	}

	void GridLayout::draw(SDL_Renderer * renderer)
	{
		// draw all windows inside the layout
		for (const auto& child : children_)
		{
			child->draw(renderer);
		}
	}

	void GridLayout::setGridPosition(Window& childWindow, int v, int h)
	{
		assert(std::find(children_.begin(), children_.end(), &childWindow) != children_.end()); // Assert that childWindow is element of GridLayout
		grid_.erase(&childWindow);
		grid_.insert(std::pair<Window*, Position>(&childWindow, { v,h }));

		maxH_ = std::max(maxH_, h);
		maxV_ = std::max(maxV_, v);
	}
}