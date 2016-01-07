#pragma once

#include "SDLGUILIB_API.h"
#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API HBoxLayout : public Window
	{
	public:
		HBoxLayout();
		HBoxLayout(Window* parentWindow);
		void setHorizontalPadding(int d);
		void setMarginTop(int t);
		void setMarginBottom(int b);
		void updateLayout();

	protected:
		int horizontalPadding_ = 5;
		int marginTop_ = 5,
			marginBottom_ = 5;
	};
}
