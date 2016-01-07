#include "stdafx.h"
#include "Gui.h"

namespace sgl
{
	Gui::Gui()
		:Window(nullptr)
		,inputManager_()
		,styleManager_()
	{
		guiRoot_ = this;	// or nullptr?
	}

	bool Gui::handleEvent(const SDL_Event& e)
	{
		// GUI itself doesn't process any events currently
		auto wasHandled = false;
		for (const auto& child : children_)
		{
			wasHandled = child->handleEvent(e);
			if (wasHandled)
			{
				break;
			}
		}
		return wasHandled;
	}

	void Gui::draw(SDL_Renderer * renderer)
	{
		// don't draw anything for a Gui object
		// draw children
		for (const auto& child : children_)
		{
			child->draw(renderer);
		}
	}

	StyleManager& Gui::getStyleManager()
	{
		return styleManager_;
	}
}
