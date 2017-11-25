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
		,relative_pos_x_(0)
		,relative_pos_y_(0)
		,screen_pos_x_(0)
		,screen_pos_y_(0)
		,is_visible_(false)
		,is_active_(true)
		,is_clicked_(false)
		,contains_mouse_(false)
		,parent_(nullptr)
		,children_()
		,event_handlers_()
		,manager_(GuiManager::GetInstance())
	{
	}

	Window::Window(Window* parent_window)
		:Window()
	{
		setParent(parent_window);
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

	void Window::addChild(Window& child_window)
	{
		child_window.setParent(this);
	}

	void Window::removeChild(Window& child_window)
	{
		child_window.setParent(nullptr);
	}

	void Window::setParent(Window* new_parent)
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
		if (new_parent != nullptr)
		{
			new_parent->children_.push_back(this);
		}
		// 3. set this windows parent
		parent_ = new_parent;
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
		auto new_pos_x = x;
		auto new_pos_y = y;
		relative_pos_x_ = new_pos_x;
		relative_pos_y_ = new_pos_y;
		if (parent_ == nullptr)
		{
			screen_pos_x_ = new_pos_x;
			screen_pos_y_ = new_pos_y;
		}
		else
		{
			screen_pos_x_ = parent_->screen_pos_x_ + new_pos_x;
			screen_pos_y_ = parent_->screen_pos_y_ + new_pos_y;
		}
	}

	Point Window::getPosition() const
	{
		return Point{ relative_pos_x_, relative_pos_y_ };
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
		is_active_ = isActive;
	}

	bool Window::isActive() const
	{
		return is_active_;
	}

	void Window::addEventCallback(EventType eventType, EventCallback handler)
	{
		event_handlers_[eventType] = handler;
	}

	void Window::removeEventCallback(EventType eventType)
	{
		event_handlers_.erase(eventType);
	}

	bool Window::isVisible()
	{
		return is_visible_;
	}

	void Window::setVisible(bool is_visible)
	{
		is_visible_ = is_visible;
		for (auto child : children_)
		{
			child->setVisible(is_visible);
		}
	}

	bool Window::handleEvent(const SDL_Event& e)
	{
		if (!is_active_ || !is_visible_)
		{
			return false;
		}
		// since child windows are on top of their parents, 
		// we first pass the event down to the children to handle.
		// If none of the children handle the event, we process it ourselves.
		auto handling_child = std::find_if(children_.begin(), children_.end(), [&](auto child) {
			return child->handleEvent(e);
		});
		auto was_handled = handling_child != children_.end();
		if (!was_handled)
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
					is_clicked_ = true;
					contains_mouse_ = true;
					was_handled = true;
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
					if (is_clicked_)
					{
						triggerMouseUp();
						triggerClicked();
					}
					is_clicked_ = false;
					contains_mouse_ = true;
					was_handled = true;
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
				auto did_contain_mouse = contains_mouse_;
				contains_mouse_ = isInsideWindowBounds(e.motion.x, e.motion.y);
				if (did_contain_mouse && contains_mouse_)
				{
					// mouse moved within the window area
					was_handled = true;
				}
				else if (did_contain_mouse && !contains_mouse_)
				{
					// mouse left the window area
					triggerMouseLeft();
					contains_mouse_ = false;
					is_clicked_ = false;
				}
				else if (!did_contain_mouse && contains_mouse_)
				{
					// mouse entered the window area
					triggerMouseEntered();
					contains_mouse_ = true;
					if((e.motion.state & SDL_BUTTON_LMASK) && hasFocus())
					{
						is_clicked_ = true;
						was_handled = true;
					}
				}
				break;
			}
			case SDL_KEYDOWN:
			{
				// handle keyboard only if we're the window with focus
				if (manager_->hasWindowFocus(this))
				{
					triggerKeyDown(e.key.keysym);
					was_handled = true;
				}
				break;
			}
			// TODO add more event types here
			default:
				// ignore event
				break;
			}
		}
		return was_handled;
	}

	bool Window::isInsideWindowBounds(int x, int y) const
	{
		return	x >= screen_pos_x_ &&
				x <= screen_pos_x_ + width_ &&
				y >= screen_pos_y_ &&
				y <= screen_pos_y_ + height_;
	}

	Window* Window::getRootParent(Window* window)
	{
		assert(window != nullptr);
		auto root_parent = window;
		while (root_parent->parent_ != nullptr)
		{
			root_parent = root_parent->parent_;
		}
		return root_parent;
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
	}

	void Window::triggerFocusLost()
	{
	}

	void Window::triggerWindowResize()
	{
	}

	void Window::triggerKeyDown(SDL_Keysym )
	{
	}
}
