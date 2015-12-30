#include "stdafx.h"

#include "Window.h"

namespace sgl
{
	Window::Window()
		:label_()
		,width_(0)
		,height_(0)
		,posX_(0)
		,posY_(0)
		,isVisible_(false)
		,isActive_(false)
		,parent_(nullptr)
		,children_()
		,canvas_(nullptr)
	{
	}

	Window::Window(Window* parentWindow, const std::string& label)
		:label_(label)
		,width_(0)
		,height_(0)
		,posX_(0)
		,posY_(0)
		,isVisible_(false)
		,isActive_(false)
		,parent_(parentWindow)
		,children_()
		,canvas_(nullptr)
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

	void Window::addChild(Window* childWindow)
	{
		children_.push_back(childWindow);
	}

	Window* Window::getParent() const
	{
		return parent_;
	}

	void Window::setSize(int width, int height)
	{
		width_ = width;
		height_ = height;
	}

	void Window::setSize(Size size)
	{
		width_ = size.width;
		height_ = size.height;
	}

	Point Window::getSize() const
	{
		return Point{ width_, height_ };
	}

	void Window::draw()
	{
		if (isVisible_)
		{
			// TODO draw window and then draw children
			for (const auto& child : children_)
			{
				child->draw();
			}
		}
	}

	void Window::setCanvas(SDL_Window& canvas)
	{
		canvas_ = &canvas;
	}

	bool Window::isVisible()
	{
		return isVisible_;
	}

	void Window::setVisible(bool isVisible)
	{
		isVisible_ = isVisible;
	}
}
