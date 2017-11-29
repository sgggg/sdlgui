#pragma once

#include "SDL.h"
#include "Event.h"
#include "EventProcessor.h"
#include "ColorTheme.h"
#include <vector>


namespace sgl
{
	class GuiManager;
	class Window;
	
	class SDLGUILIB_API InputHandler : public EventProcessor
	{
	public:
		InputHandler(GuiManager* manager);

		virtual bool handleEvent(const SDL_Event& e) override;

	private:
		GuiManager* manager_;

		InputHandler& operator=(const InputHandler&) = delete;
		InputHandler(const InputHandler&) = delete;
	};
}
