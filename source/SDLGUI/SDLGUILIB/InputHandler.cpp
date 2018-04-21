#include "stdafx.h"

#include "InputHandler.h"
#include "GuiManager.h"
#include "Window.h"
#include <assert.h>

namespace sgl
{
	InputHandler::InputHandler(GuiManager* manager)
		:manager_(manager)
	{
		assert(manager_ != nullptr);
	}


	bool InputHandler::handleEvent(const SDL_Event& e)
	{
		// pass the event top-down through the stack, until we find a window that handles it
		const auto& window_stack = manager_->getWindowStack();
		std::find_if(window_stack.begin(), window_stack.end(), [&](auto* window) {
			return window->handleEvent(e);
			//return window->handleEvent(toEvent(e));
		});
		return true;
	}

	Event InputHandler::toEvent(const SDL_Event& e)
	{
		return Event();
	}
}
