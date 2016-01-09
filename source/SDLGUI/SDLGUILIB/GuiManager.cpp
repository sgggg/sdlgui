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
		if (window->getParent() == nullptr)
		{
			windowStack_.push_front(window);
		}
		windows_.push_back(window);
	}

	void GuiManager::unregisterWindow(Window* window)
	{
		// currently O(#windows), could be O(1)
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
	}

	void GuiManager::setWindowFocus(Window* windowWithFocus)
	{
		auto windowIt = std::find(std::begin(windowStack_), std::end(windowStack_), windowWithFocus);
		if (windowIt != std::end(windowStack_))
		{
			windowStack_.erase(windowIt);
			windowStack_.push_front(windowWithFocus);
		}
		else
		{
			assert(false);	// setting focus to unregistered window!
		}
	}

	bool GuiManager::hasWindowFocus(const Window* window) const
	{
		if (windowStack_.size() == 0)
		{
			return false;
		}
		return *std::begin(windowStack_) == window;
	}

	WindowId GuiManager::getAvailableWindowId()
	{
		return windowIdCounter_++;
	}

	void GuiManager::freeWindowId(WindowId id)
	{
		// TODO implement
	}

	void GuiManager::updateWindowStack()
	{
		// TODO generate new window stack according to windows in windows_
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
