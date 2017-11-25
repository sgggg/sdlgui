#pragma once

#include "SDLGUILIB_API.h"
#include "Window.h"
#include "Utility.h"
#include <map>

namespace sgl
{
	struct GridPolicy {
		unsigned int vertical_position;
		unsigned int horizontal_position;
		unsigned int width;
		unsigned int height;
	};

	class SDLGUILIB_API GridLayout : public Window
	{
	public:
		GridLayout();
		GridLayout(Window* parent_window);
		void setPadding(int top, int bottom, int left, int right);
		void setMargin(int top, int bottom, int left, int right);
		void updateLayout();

		virtual void draw(SDL_Renderer* renderer) override;
		void setGridPolicy(Window& child_window, unsigned int vertical_position, unsigned int horizontal_position, unsigned int height = 1, unsigned int width = 1);

	protected:
		int padding_top_ = 5;		// Padding in pixels
		int padding_bottom_ = 5;
		int padding_left_ = 5;
		int padding_right_ = 5;
		int margin_top_ = 5;		// Margin in pixels
		int margin_bottom_ = 5;
		int margin_left_ = 5;
		int margin_right_ = 5;
		unsigned int max_vertical_index_ = 0;		// Maximum index of elements in vertical/horizontal direction
		unsigned int max_horizontal_index_ = 0;			// Index starts at 0
		std::map<Window*, GridPolicy> grid_;
	};
}
