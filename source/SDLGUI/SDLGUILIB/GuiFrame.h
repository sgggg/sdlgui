#pragma once

#include "Window.h"
#include "Event.h"
#include "InputManager.h"

namespace sgl
{
	class GuiFrame
	{
	public:
		virtual void addEventHandler(EventType eventType, WindowId id, EventHandler handler);
		virtual WindowId getNewId();

	private:
		InputHandler inputHandler;

		GuiFrame(const GuiFrame&) = delete;
		GuiFrame operator=(const GuiFrame&) = delete;
	};
}
