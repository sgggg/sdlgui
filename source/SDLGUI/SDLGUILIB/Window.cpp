#include "stdafx.h"

#include "Window.h"

namespace sgl
{
	Window::Window()
		:id_(-1)
		,label_()
		,width_(0)
		,height_(0)
		,relativePosX_(0)
		,relativePosY_(0)
		,screenPosX_(0)
		,screenPosY_(0)
		,hasTitleBar_(false)
		,isVisible_(false)
		,isActive_(false)
		,isClicked_(false)
		,containsMouse_(false)
		,parent_(nullptr)
		,children_()
	{
	}

	Window::Window(Window* parentWindow, const std::string& label)
		:Window()
	{
		label_ = label;
		parent_ = parentWindow;
		setPosition(0, 0);
	}
	
	std::string Window::getLabel() const
	{
		return label_;
	}

	void Window::setLabel(const std::string& text)
	{
		label_ = text;
	}

	void Window::addChild(Window& childWindow)
	{
		children_.push_back(&childWindow);
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

	Size Window::getSize() const
	{
		return Size{ width_, height_ };
	}

	void Window::setPosition(int x, int y)
	{
		auto newPosX = x;
		auto newPosY = y;
		// TODO check that window is always positioned fully inside parent window
		relativePosX_ = newPosX;
		relativePosY_ = newPosY;
		if (parent_ == nullptr)
		{
			screenPosX_ = newPosX;
			screenPosY_ = newPosY;
		}
		else
		{
			screenPosX_ = parent_->screenPosX_ + newPosX;
			screenPosY_ = parent_->screenPosY_ + newPosY;
		}
	}

	Point Window::getPosition() const
	{
		return Point{ relativePosX_, relativePosY_ };
	}

	void Window::addEventHandler(EventType eventType, EventHandler handler)
	{
		eventHandlers_[eventType] = handler;
	}

	void Window::draw(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			SDL_Rect outlineRect = { screenPosX_, screenPosY_, width_, height_ };
			SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
			SDL_RenderDrawRect(renderer, &outlineRect);

			renderTextAtPos(renderer, label_, screenPosX_, screenPosY_, { 0,0,0 }, {0xC0, 0xC0, 0xC0});

			// TODO draw window and then draw children
			for (const auto& child : children_)
			{
				child->draw(renderer);
			}
		}
	}

	bool Window::isVisible()
	{
		return isVisible_;
	}

	void Window::setVisible(bool isVisible)
	{
		isVisible_ = isVisible;
	}

	bool Window::handleEvent(const SDL_Event& e)
	{
		// since child windows usually are on top of their parents, 
		// we first pass the event down to the children to handle.
		// If none of the children handle the event, we process it ourselves.
		auto wasHandled = false;
		for (const auto& child : children_)
		{
			wasHandled = child->handleEvent(e);
			if (wasHandled)
			{
				break;
			}
		}
		if (!wasHandled)
		{
			// if the event was not handled by any child
			// check if it concerns this window
			switch (e.type)
			{
			case SDL_MOUSEBUTTONDOWN:
			{
				// Uint32		type		the event type; SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP
				// Uint32		timestamp	timestamp of the event
				// Uint32		windowID	the window with mouse focus, if any
				// Uint32		which		the mouse instance id, or SDL_TOUCH_MOUSEID; see Remarks for details
				// Uint8		button		the button that changed; see Remarks for details
				// Uint8		state		the state of the button; SDL_PRESSED or SDL_RELEASED
				// Uint8		clicks		1 for single - click, 2 for double - click, etc. (>= SDL 2.0.2)
				// Sint32		x			X coordinate, relative to window
				// Sint32		y			Y coordinate, relative to window
				if (isInsideWindowBounds(e.button.x, e.button.y) &&
					e.button.button == SDL_BUTTON_LEFT &&
					e.button.state == SDL_PRESSED)
				{
					// normal left click inside this window
					isActive_ = true;
					isClicked_ = true;
					containsMouse_ = true;
					wasHandled = true;
					triggerMouseDown();
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				if (isInsideWindowBounds(e.button.x, e.button.y) &&
					e.button.button == SDL_BUTTON_LEFT &&
					e.button.state == SDL_RELEASED)
				{
					// normal left mouse up inside this window
					if (isClicked_)
					{
						triggerMouseUp();
						triggerClicked();
					}
					isClicked_ = false;
					containsMouse_ = true;
					wasHandled = true;
				}
				break;
			}
			case SDL_MOUSEMOTION:
			{
				// we have to cover:
				// - drag & drop
				// - resizing the window
				// - releasing mouse-down when leaving the window with pressed lmouse
				// - resuming mouse-down when re-entering with pressed lmouse
				// TODO
				auto didContainMouse = containsMouse_;
				containsMouse_ = isInsideWindowBounds(e.motion.x, e.motion.y);
				if (didContainMouse && containsMouse_)
				{
					// mouse moved within the window area
					wasHandled = true;
				}
				else if (didContainMouse && !containsMouse_)
				{
					// mouse left the window area
					triggerMouseLeft();
					containsMouse_ = false;
					isClicked_ = false;
				}
				else if (!didContainMouse && containsMouse_)
				{
					// mouse entered the window area
					triggerMouseEntered();
					wasHandled = true;
					containsMouse_ = true;
					// TODO set isClicked_ if mouse1 is pressed
				}
				break;
			}
			// TODO add more event types
			default:
				// ignore event
				break;
			}
		}
		return wasHandled;
	}

	bool Window::isInsideWindowBounds(int x, int y) const
	{
		return	x >= screenPosX_ &&
				x <= screenPosX_ + width_ &&
				y >= screenPosY_ &&
				y <= screenPosY_ + height_;
	}

	void Window::triggerClicked()
	{
		std::cout << "Window " << label_ << ": clicked" << std::endl;
	}

	void Window::triggerDoubleClicked()
	{
		std::cout << "Window " << label_ << ": double clicked" << std::endl;
	}

	void Window::triggerMouseEntered()
	{
		std::cout << "Window " << label_ << ": mouse entered" << std::endl;
	}

	void Window::triggerMouseLeft()
	{
		std::cout << "Window " << label_ << ": mouse left" << std::endl;
	}

	void Window::triggerMouseDown()
	{
		std::cout << "Window " << label_ << ": mouse down" << std::endl;
	}

	void Window::triggerMouseUp()
	{
		std::cout << "Window " << label_ << ": mouse up" << std::endl;
	}
}
