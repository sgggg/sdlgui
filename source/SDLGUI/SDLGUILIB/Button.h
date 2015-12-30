#pragma once

#include "Window.h"

namespace sgl
{
	class SDLGUILIB_API Button : public Window
	{
	public:
		Button();
		Button(Window* parent, const std::string& label);
	};
}
