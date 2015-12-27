#pragma once

#include "SDLGUILIB_API.h"

namespace sgl
{
	class SDLGUILIB_API Drawable
	{
	public:
		virtual void draw() = 0;
		virtual bool isVisible() = 0;
		virtual void setVisible(bool isVisible) = 0;
		virtual ~Drawable() {};
	};
}