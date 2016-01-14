#include "stdafx.h"
#include "GridLayout.h"
#include <assert.h>
#include <algorithm>

namespace sgl
{
	GridLayout::GridLayout()
		:Window()
		,grid_()
	{
	}

	GridLayout::GridLayout(Window* parentWindow)
		:Window(parentWindow)
		,grid_()
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
			gridElem.first->setSize( widthPerChild + (widthPerChild + paddingLeft_ + paddingRight_) * (gridElem.second.width -1),
									 heightPerChild + (heightPerChild + paddingTop_ + paddingBottom_) * (gridElem.second.height - 1));
			gridElem.first->setPosition( marginLeft_ + gridElem.second.hPos * widthPerCell  + paddingLeft_,
										 marginTop_  + gridElem.second.vPos * heightPerCell + paddingTop_ );
		}
	}

	void GridLayout::draw(SDL_Renderer* renderer)
	{
		// draw all windows inside the layout
		for (const auto& child : children_)
		{
			child->draw(renderer);
		}
	}

	void GridLayout::setGridPolicy(Window& childWindow, unsigned int vPos, unsigned int hPos, unsigned int height, unsigned int width)
	{
		assert(std::find(children_.begin(), children_.end(), &childWindow) != children_.end()); // Assert that childWindow is element of GridLayout
		grid_.erase(&childWindow);
		grid_.insert(std::make_pair(&childWindow, gridPolicy{vPos, hPos, width, height}));

		maxH_ = std::max(maxH_, hPos);
		maxV_ = std::max(maxV_, vPos);
	}
}