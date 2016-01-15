#pragma once

#include "SDLGUILIB_API.h"
#include "Window.h"
#include "Utility.h"
#include <map>

namespace sgl
{
	struct gridPolicy {
		unsigned int vPos;
		unsigned int hPos;
		unsigned int width;
		unsigned int height;
	};

	class SDLGUILIB_API GridLayout : public Window
	{
	public:
		GridLayout();
		GridLayout(Window* parentWindow);
		void setPadding(int top, int bottom, int left, int right);
		void setMargin(int top, int bottom, int left, int right);
		void updateLayout();

		virtual void draw(SDL_Renderer* renderer) override;
		void setGridPolicy(Window& childWindow, unsigned int vPos, unsigned int hPos, unsigned int height = 1, unsigned int width = 1);

	protected:
		int paddingTop_ = 5,	// Padding in pixels
			paddingBottom_ = 5,
			paddingLeft_ = 5,
			paddingRight_ = 5;
		int marginTop_ = 5,		// Margin in pixels
			marginBottom_ = 5,
			marginLeft_ = 5,
			marginRight_ = 5;
		unsigned int maxV_ = 0,			// Maximum index of elements in vertical/horizontal direction
					 maxH_ = 0;			// Index starts at 0
		std::map<Window*, gridPolicy> grid_;
	};
}
