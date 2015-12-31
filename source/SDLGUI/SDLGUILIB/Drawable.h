#pragma once

#include "SDLGUILIB_API.h"
#include "SDL.h"

namespace sgl
{
	class SDLGUILIB_API Drawable
	{
	public:
		virtual void draw(SDL_Renderer& renderer) = 0;
		virtual bool isVisible() = 0;
		virtual void setVisible(bool isVisible) = 0;
		virtual ~Drawable() {};
	};
}