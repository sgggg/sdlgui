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
		// a parent gets the event only when no children claims the input as exclusive
		for (auto window : manager_->getWindowStack())
		{
			auto wasCaptured = window->handleEvent(e);
			if (wasCaptured)
			{
				break;
			}
		}
		return true;
	}

	bool InputHandler::handleWindowWithChildren(Window* window, const SDL_Event& e)
	{
		return false;
	}
}
