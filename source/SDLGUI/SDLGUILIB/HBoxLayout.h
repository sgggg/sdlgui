#pragma once

#include "SDLGUILIB_API.h"
#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API HBoxLayout : public Window
	{
	public:
		HBoxLayout();
		HBoxLayout(Window* parent_window);
		void setHorizontalPadding(int d);
		void setMarginTop(int t);
		void setMarginBottom(int b);
		void updateLayout();

		virtual void draw(SDL_Renderer* renderer) override;

	protected:
		int horizontal_padding_ = 5;
		int margin_top_ = 5;
		int margin_bottom_ = 5;
	};
}
