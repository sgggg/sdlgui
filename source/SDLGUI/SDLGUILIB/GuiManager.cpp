#include "stdafx.h"
#include "GuiManager.h"
#include "Window.h"
#include <assert.h>

namespace sgl
{
	void DrawGui(SDL_Renderer* renderer)
	{
		GuiManager::GetInstance()->drawGui(renderer);
	}

	bool HandleEvent(SDL_Event* e)
	{
		return GuiManager::GetInstance()->getInputHandler().handleEvent(*e);
	}

	GuiManager* GuiManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance.reset(new GuiManager());
		}
		return instance.get();
	}

	InputHandler & GuiManager::getInputHandler()
	{
		return inputHandler_;
	}

	StyleManager & GuiManager::getStyleManager()
	{
		return styleManager_;
	}

	std::list<Window*>& GuiManager::getWindowStack()
	{
		return windowStack_;
	}

	void GuiManager::drawGui(SDL_Renderer* renderer)
	{
		// we draw all the windows that don't have parents
		// because all those with parents are drawn by their 
		// parents draw() function
		// we're going through the list in reverse order so that the first item is drawn on top
		for (auto windowIt = std::rbegin(windowStack_); windowIt != std::rend(windowStack_); ++windowIt)
		{
			(*windowIt)->draw(renderer);
		}
	}

	void GuiManager::registerWindow(Window* window, WindowId& id)
	{
		// each window must have a unique window ID
		if (id == -1)
		{
			id = getAvailableWindowId();
		}
		windows_.push_back(window);
		// the draw order of top-level windows is saved in the window stack
		if (window->getParent() == nullptr)
		{
			windowStack_.push_front(window);
		}
		// if this is the first window created, set it as focused
		if (windows_.size() == 1)
		{
			windowWithFocus_ = window;
		}
	}

	void GuiManager::unregisterWindow(Window* window)
	{
		// TODO currently O(#windows), could be O(1)
		// remove the window from all data structures
		auto windowIt = std::find(std::begin(windows_), std::end(windows_), window);
		if (windowIt != std::end(windows_))
		{
			windows_.erase(windowIt);
		}
		auto windowStackIt = std::find(std::begin(windowStack_), std::end(windowStack_), window);
		if (windowStackIt != std::end(windowStack_))
		{
			windowStack_.erase(windowStackIt);
		}
		freeWindowId(window->GetId());
		// move focus to another existing window, if the destroyed had focus
		if (window == windowWithFocus_)
		{
			if (windowStack_.size() > 0)
			{
				windowWithFocus_ = *std::begin(windowStack_);
			}
			else
			{
				// this one was the last window
				windowWithFocus_ = nullptr;
			}
		}
	}

	void GuiManager::setWindowFocus(Window* windowWithFocus)
	{
		assert(windowWithFocus != nullptr);
		if (windowWithFocus_ != windowWithFocus)
		{
			auto previousFocusWindow = windowWithFocus_;
			// first we remove focus from the old window
			// this is done by setting windowWithFocus_ to nullptr
			windowWithFocus_ = nullptr;
			// then we notify the window that it lost focus
			// this also triggers user-defined event callbacks
			previousFocusWindow->triggerFocusLost();
			// then we set focus to the new window
			windowWithFocus_ = windowWithFocus;
			// then we notify the new window that it gained focus
			// this also triggers user-defined event callbacks
			windowWithFocus->triggerFocusGained();
		}
	}

	bool GuiManager::hasWindowFocus(const Window* window) const
	{
		if (windowWithFocus_ == nullptr)
		{
			return false;
		}
		else
		{
			return windowWithFocus_ == window;
		}
	}

	WindowId GuiManager::getAvailableWindowId()
	{
		return windowIdCounter_++;
	}

	void GuiManager::freeWindowId(WindowId id)
	{
		// TODO implement
	}

	void GuiManager::stackOnTop(Window* newTopWindow)
	{
		auto windowIt = std::find(std::begin(windowStack_), std::end(windowStack_), newTopWindow);
		assert(windowIt != std::end(windowStack_));	// setting focus to unregistered window!
		if (windowIt != std::begin(windowStack_))
		{
			// move to front of window stack if it is not already
			windowStack_.erase(windowIt);
			windowStack_.push_front(newTopWindow);
		}
	}

	void GuiManager::updateWindowStack()
	{
		windowStack_.clear();
		for (const auto win : windows_)
		{
			if (win->getParent() == nullptr)
			{
				windowStack_.push_back(win);
			}
		}
	}

	void GuiManager::setApplicationTime(int64_t time)
	{
		applicationTime_ = time;
	}

	int64_t GuiManager::getApplicationTime() const
	{
		return applicationTime_;
	}

	GuiManager::GuiManager()
		:inputHandler_(this)
		,styleManager_()
		,windows_()
		,windowStack_()
		,windowWithFocus_(nullptr)
		,windowIdCounter_(0)
		,applicationTime_(0)
	{
	}

	std::unique_ptr<GuiManager> GuiManager::instance;
}
