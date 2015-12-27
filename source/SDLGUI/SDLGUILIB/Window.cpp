#include "stdafx.h"

#include "Window.h"

namespace sgl
{
	Window::Window()
		:label_()
	{
	}

	Window::~Window()
	{
	}
	
	std::string Window::getLabel() const
	{
		return label_;
	}

	void Window::setLabel(const std::string& text)
	{
		label_ = text;
	}

}
