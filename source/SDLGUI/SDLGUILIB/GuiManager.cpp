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
	/*
	EventScheduler & GuiManager::getEventScheduler()
	{
		return scheduler_;
	}*/

	std::list<Window*>& GuiManager::getWindows()
	{
		return windows_;
	}

	void GuiManager::drawGui(SDL_Renderer* renderer)
	{
		// we draw all the windows that don't have parents
		// because all those with parents are drawn by their 
		// parents draw() function
		// TODO draw all windows from here in the order given by their 
		// parent/child relationships represented by windows_
		// so that the window with focus is always on top
		for (auto windowIt = std::rbegin(windows_); windowIt != std::rend(windows_); ++windowIt)
		{
			if ((*windowIt)->getParent() == nullptr)
			{
				(*windowIt)->draw(renderer);
			}
		}
	}

	void GuiManager::registerWindow(Window* window, WindowId& id)
	{
		if (id == -1)
		{
			id = getAvailableWindowId();
		}
		windows_.push_back(window);
	}

	void GuiManager::unregisterWindow(Window* window)
	{
		auto windowIt = std::find(std::begin(windows_), std::end(windows_), window);
		if (windowIt != std::end(windows_))
		{
			windows_.erase(windowIt);
		}
		// TODO free window id
		//freeWindowId(window->GetId());
	}

	void GuiManager::setWindowFocus(Window* windowWithFocus)
	{
		auto windowIt = std::find(std::begin(windows_), std::end(windows_), windowWithFocus);
		if (windowIt != std::end(windows_))
		{
			windows_.erase(windowIt);
			windows_.push_front(windowWithFocus);
		}
		else
		{
			assert(false);	// unregistered window!
		}
	}

	bool GuiManager::hasWindowFocus(const Window* window) const
	{
		if (windows_.size() == 0)
		{
			return false;
		}
		return *std::begin(windows_) == window;
	}

	WindowId GuiManager::getAvailableWindowId()
	{
		return windowIdCounter_++;
	}

	GuiManager::GuiManager()
		:inputHandler_(this)
		,styleManager_()
		,windows_()
		,windowStack_()
		,windowIdCounter_(0)
	{
	}

	std::unique_ptr<GuiManager> GuiManager::instance;
}
