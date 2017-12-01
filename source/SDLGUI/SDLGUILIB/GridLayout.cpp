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

	void GridLayout::setGridPolicy(Window& child_window, int horizontal_position, int vertical_position, int width, int height)
	{
		assert(std::find(children_.begin(), children_.end(), &child_window) != children_.end()); // Assert that child_window is element of GridLayout
		grid_.erase(&child_window);
		grid_.insert(std::make_pair(&child_window, GridPolicy{ vertical_position, horizontal_position, width, height }));

		max_horizontal_index_ = std::max(max_horizontal_index_, horizontal_position);
		max_vertical_index_ = std::max(max_vertical_index_, vertical_position);
	}

	void GridLayout::updateLayout()
	{
		const auto width_per_cell = (size_.width - margin_left_ - margin_right_) / (max_horizontal_index_ + 1);	//use (max_horizontal_index_+1) because positioning starts at index 0
		const auto height_per_cell = (size_.height - margin_top_ - margin_bottom_) / (max_vertical_index_ + 1);
		const auto width_per_child = width_per_cell - padding_left_ - padding_right_;
		const auto height_per_child = height_per_cell - padding_top_ - padding_bottom_;
		for (auto grid_element : grid_)
		{
			const auto child_x = margin_left_ + grid_element.second.horizontal_position * width_per_cell + padding_left_;
			const auto child_y = margin_top_ + grid_element.second.vertical_position * height_per_cell + padding_top_;
			const auto child_width = width_per_child + (width_per_child + padding_left_ + padding_right_) * (grid_element.second.width - 1);
			const auto child_height = height_per_child + (height_per_child + padding_top_ + padding_bottom_) * (grid_element.second.height - 1);
			grid_element.first->setSize(child_width, child_height);
			grid_element.first->setPosition(child_x, child_y);
		}
	}

	void GridLayout::draw(SDL_Renderer* renderer)
	{
		for (const auto& child : children_)
		{
			child->draw(renderer);
		}
	}
}