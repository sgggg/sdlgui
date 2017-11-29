#include "stdafx.h"
#include "GridLayout.h"
#include <assert.h>
#include <algorithm>

namespace sgl
{
	GridLayout::GridLayout() :
		Window(),
		grid_()
	{
	}

	GridLayout::GridLayout(Window* parent_window) :
		Window(parent_window),
		grid_()
	{
	}

	void GridLayout::setPadding(int top, int bottom, int left, int right)
	{
		padding_top_ = top;
		padding_bottom_ = bottom;
		padding_left_ = left;
		padding_right_ = right;
	}

	void GridLayout::setMargin(int top, int bottom, int left, int right)
	{
		margin_top_ = top;
		margin_bottom_ = bottom;
		margin_left_ = left;
		margin_right_ = right;
	}

	void GridLayout::updateLayout()
	{
		const auto width_per_cell = (size_.width - margin_left_ - margin_right_) / (max_horizontal_index_ + 1);	//use (max_horizontal_index_+1) because positioning starts at index 0
		const auto height_per_cell = (size_.height - margin_top_ - margin_bottom_) / (max_vertical_index_ + 1);
		const auto width_per_child = width_per_cell - padding_left_ - padding_right_;
		const auto height_per_child = height_per_cell - padding_top_ - padding_bottom_;
		for (auto grid_element : grid_)
		{
			grid_element.first->setSize(width_per_child + (width_per_child + padding_left_ + padding_right_) * (grid_element.second.width - 1),
				height_per_child + (height_per_child + padding_top_ + padding_bottom_) * (grid_element.second.height - 1));
			grid_element.first->setPosition(margin_left_ + grid_element.second.horizontal_position * width_per_cell + padding_left_,
				margin_top_ + grid_element.second.vertical_position * height_per_cell + padding_top_);
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

	void GridLayout::setGridPolicy(Window& child_window, unsigned int horizontal_position, unsigned int vertical_position, unsigned int width, unsigned int height)
	{
		assert(std::find(children_.begin(), children_.end(), &child_window) != children_.end()); // Assert that child_window is element of GridLayout
		grid_.erase(&child_window);
		grid_.insert(std::make_pair(&child_window, GridPolicy{vertical_position, horizontal_position, width, height}));

		max_horizontal_index_ = std::max(max_horizontal_index_, horizontal_position);
		max_vertical_index_ = std::max(max_vertical_index_, vertical_position);
	}
}