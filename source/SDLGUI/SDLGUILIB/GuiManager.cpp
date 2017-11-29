#include "stdafx.h"

#include "GuiManager.h"
#include "Window.h"

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

	void SetApplicationTime(std::chrono::milliseconds absoluteTime)
	{
		GuiManager::GetInstance()->setApplicationTime(absoluteTime);
	}

	std::chrono::milliseconds GetApplicationTime()
	{
		return GuiManager::GetInstance()->getApplicationTime();
	}

	GuiManager* GuiManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance.reset(new GuiManager());
		}
		return instance.get();
	}

	InputHandler& GuiManager::getInputHandler()
	{
		return input_handler_;
	}

	StyleManager& GuiManager::getStyleManager()
	{
		return style_manager_;
	}

	RenderAssistant& GuiManager::getRenderAssistant()
	{
		return render_assistant_;
	}

	std::list<Window*>& GuiManager::getWindowStack()
	{
		return window_stack_;
	}

	void GuiManager::drawGui(SDL_Renderer* renderer)
	{
		// we draw all the windows that don't have parents
		// because all those with parents are drawn by their 
		// parents draw() function
		// we're going through the list in reverse order so that the first item is drawn on top
		std::for_each(window_stack_.rbegin(), window_stack_.rend(), [=](auto* window) {
			window->draw(renderer);
		});
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
			window_stack_.push_front(window);
		}
		// if this is the first window created, set it as focused
		if (windows_.size() == 1)
		{
			window_with_focus_ = window;
		}
	}

	void GuiManager::unregisterWindow(Window* window)
	{
		// TODO currently O(#windows), could be O(1)
		// remove the window from all data structures
		auto window_it = std::find(std::begin(windows_), std::end(windows_), window);
		if (window_it != std::end(windows_))
		{
			windows_.erase(window_it);
		}
		auto window_stack_it = std::find(std::begin(window_stack_), std::end(window_stack_), window);
		if (window_stack_it != std::end(window_stack_))
		{
			window_stack_.erase(window_stack_it);
		}
		freeWindowId(window->getId());
		// move focus to another existing window, if the destroyed had focus
		if (window == window_with_focus_)
		{
			if (!window_stack_.empty())
			{
				window_with_focus_ = *std::begin(window_stack_);
			}
			else
			{
				window_with_focus_ = nullptr;
			}
		}
	}

	void GuiManager::setWindowFocus(Window* window_with_focus)
	{
		assert(window_with_focus != nullptr);
		if (window_with_focus_ != window_with_focus)
		{
			auto previous_focus_window = window_with_focus_;
			// first we remove focus from the old window
			// this is done by setting window_with_focus_ to nullptr
			window_with_focus_ = nullptr;
			// then we notify the window that it lost focus
			// this also triggers user-defined event callbacks
			previous_focus_window->triggerFocusLost();
			// then we set focus to the new window
			window_with_focus_ = window_with_focus;
			// then we notify the new window that it gained focus
			// this also triggers user-defined event callbacks
			window_with_focus->triggerFocusGained();
		}
	}

	bool GuiManager::hasWindowFocus(const Window* window) const
	{
		return window_with_focus_ == window;
	}

	WindowId GuiManager::getAvailableWindowId()
	{
		return window_id_counter_++;
	}

	void GuiManager::freeWindowId(WindowId /*id*/)
	{
		// TODO implement
	}

	void GuiManager::stackOnTop(Window* new_top_window)
	{
		auto window_it = std::find(std::begin(window_stack_), std::end(window_stack_), new_top_window);
		assert(window_it != std::end(window_stack_));	// setting focus to unregistered window!
		if (window_it != std::begin(window_stack_))
		{
			// move to front of window stack if it is not already
			window_stack_.erase(window_it);
			window_stack_.push_front(new_top_window);
		}
	}

	void GuiManager::updateWindowStack()
	{
		window_stack_.clear();
		std::copy_if(windows_.begin(), windows_.end(), std::back_inserter(window_stack_), [](auto* window) {
			return window->getParent() == nullptr;
		});
	}

	void GuiManager::setApplicationTime(std::chrono::milliseconds time)
	{
		application_time_ = time;
	}

	std::chrono::milliseconds GuiManager::getApplicationTime() const
	{
		return application_time_;
	}

	GuiManager::GuiManager()
		:input_handler_(this)
		,style_manager_()
		,render_assistant_()
		,windows_()
		,window_stack_()
		,window_with_focus_(nullptr)
		,window_id_counter_(0)
		,application_time_(0)
	{
	}

	std::unique_ptr<GuiManager> GuiManager::instance;
}
