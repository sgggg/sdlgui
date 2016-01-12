#include "stdafx.h"

#include "Window.h"
#include "GuiManager.h"
#include <assert.h>

namespace sgl
{
	Window::Window()
		:id_(-1)
		,width_(0)
		,height_(0)
		,relativePosX_(0)
		,relativePosY_(0)
		,screenPosX_(0)
		,screenPosY_(0)
		,isVisible_(false)
		,isActive_(true)
		,isClicked_(false)
		,containsMouse_(false)
		,parent_(nullptr)
		,children_()
		,eventHandlers_()
		,manager_(GuiManager::GetInstance())
	{
	}

	Window::Window(Window* parentWindow)
		:Window()
	{
		setParent(parentWindow);
		setPosition(0, 0);
		manager_->registerWindow(this, id_);
		std::cout << "Window " << id_ << " constructed and registered" << std::endl;
	}

	Window::~Window()
	{
		manager_->unregisterWindow(this);
		setParent(nullptr);
		for (auto child : children_)
		{
			child->setParent(nullptr);
		}
	}

	WindowId Window::GetId() const
	{
		return id_;
	}

	void Window::addChild(Window& childWindow)
	{
		childWindow.setParent(this);
	}

	void Window::removeChild(Window& childWindow)
	{
		childWindow.setParent(nullptr);
	}

	void Window::setParent(Window* newParent)
	{
		// 1. remove this window from children of old parent, if there was one
		if (parent_ != nullptr)
		{
			auto childIt = std::find(parent_->children_.begin(), parent_->children_.end(), this);
			if (childIt != parent_->children_.end())
			{
				parent_->children_.erase(childIt);
			}
		}
		// 2. add this window to new parents children if new parent exists
		if (newParent != nullptr)
		{
			newParent->children_.push_back(this);
		}
		// 3. set this windows parent
		parent_ = newParent;
		assert(parent_ != this);	// window can't be its own child
		// 4. notify manager that parent relationships have changed
		manager_->updateWindowStack();
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

	Size Window::getSize() const
	{
		return Size{ width_, height_ };
	}

	//void Window::setSizeFixed(bool isFixed)
	//{
	//	isSizeFixed_ = isFixed;
	//}

	void Window::setPosition(int x, int y)
	{
		// TODO check that window is always positioned fully inside parent window
		// TODO make sure that all child windows are moved together with their parent
		auto newPosX = x;
		auto newPosY = y;
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

	//void Window::setPositionFixed(bool isFixed)
	//{
	//	isPositionFixed_ = isFixed;
	//}

	void Window::setFocus()
	{
		manager_->setWindowFocus(this);
		if (parent_ == nullptr)
		{
			manager_->stackOnTop(this);
		}
		else
		{
			manager_->stackOnTop(getRootParent(this));
		}
	}

	bool Window::hasFocus() const
	{
		return manager_->hasWindowFocus(this);
	}

	void Window::setActive(bool isActive)
	{
		isActive_ = isActive;
	}

	bool Window::isActive() const
	{
		return isActive_;
	}

	void Window::addEventCallback(EventType eventType, EventCallback handler)
	{
		eventHandlers_[eventType] = handler;
	}

	void Window::removeEventCallback(EventType eventType)
	{
		eventHandlers_.erase(eventType);
	}

	bool Window::isVisible()
	{
		return isVisible_;
	}

	void Window::setVisible(bool isVisible)
	{
		isVisible_ = isVisible;
		for (auto child : children_)
		{
			child->setVisible(isVisible);
		}
	}

	bool Window::handleEvent(const SDL_Event& e)
	{
		if (!isActive_)
		{
			return false;
		}
		// since child windows are on top of their parents, 
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
					setFocus();
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
					if(e.motion.state & SDL_BUTTON_LMASK && hasFocus())
					{
						isClicked_ = true;
					}
					// TODO set isClicked_ if mouse1 is pressed
				}
				break;
			}
			case SDL_KEYDOWN:
			{
				// handle keyboard only if we're the window with focus
				if (manager_->hasWindowFocus(this))
				{
					auto keyname = SDL_GetKeyName(e.key.keysym.sym);
					std::cout << keyname << std::endl;
					wasHandled = true;
				}
				break;
			}
			// TODO add more event types here
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

	Window* Window::getRootParent(Window* window)
	{
		assert(window != nullptr);
		auto rootParent = window;
		while (rootParent->parent_ != nullptr)
		{
			rootParent = rootParent->parent_;
		}
		return rootParent;
	}
	
	void Window::triggerClicked()
	{
	}

	void Window::triggerDoubleClicked()
	{
	}

	void Window::triggerMouseEntered()
	{
	}

	void Window::triggerMouseLeft()
	{
	}

	void Window::triggerMouseDown()
	{
	}

	void Window::triggerMouseUp()
	{
	}

	void Window::triggerFocusGained()
	{
		auto isChild = parent_ != nullptr;
		std::cout << "window " << id_ << " gained focus " << (isChild ? "(child)" : "(top-level)") << std::endl;
	}

	void Window::triggerFocusLost()
	{
		std::cout << "window " << id_ << " lost focus" << std::endl;
	}

	void Window::triggerWindowResize()
	{
	}
}
