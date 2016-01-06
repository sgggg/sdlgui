#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API TextLabel : public Window
	{
	public:
		TextLabel();
		TextLabel(Window* parent, const std::string& text);

		// inherited functions
		virtual void draw(SDL_Renderer* renderer) override;
	};
}
