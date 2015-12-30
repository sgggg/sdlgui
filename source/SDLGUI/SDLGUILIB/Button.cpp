#include "stdafx.h"
#include "Button.h"

namespace sgl
{
	Button::Button()
		:Window()
	{
	}

	Button::Button(Window* parent, const std::string& label)
		:Window(parent, label)
	{
		parent->addChild(this);
	}
}