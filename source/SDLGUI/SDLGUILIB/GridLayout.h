#pragma once

#include "SDLGUILIB_API.h"
#include "Window.h"
#include "Utility.h"
#include <map>

namespace sgl
{
	class SDLGUILIB_API GridLayout : public Window
	{
	public:
		GridLayout();
		GridLayout(Window* parentWindow);
		void setPadding(int top, int bottom, int left, int right);
		void setMargin(int top, int bottom, int left, int right);
		void updateLayout();

		virtual void draw(SDL_Renderer* renderer) override;
		void setGridPosition(Window& childWindow, int v, int h);

	protected:
		int paddingTop_ = 5,
			paddingBottom_ = 5,
			paddingLeft_ = 5,
			paddingRight_ = 5;
		int marginTop_ = 5,
			marginBottom_ = 5,
			marginLeft_ = 5,
			marginRight_ = 5;
		int maxV_ = 0,
			maxH_ = 0;
		std::map<Window*, Point> grid_;
	};
}
