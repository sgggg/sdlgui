#pragma once

#include "SDL.h"
#include "SDLGUILIB_API.h"
#include "Event.h"
#include <vector>


// Note: do not use any of this shit... still work in progress

namespace sgl
{
	class Window;
	class InputHandler;

	SDLGUILIB_API int GlobalInitialize();
	SDLGUILIB_API int GlobalCleanup();
	SDLGUILIB_API void HandleInput(SDL_Event& e);
	SDLGUILIB_API InputHandler& GetGlobalInputHandler();
	
	class SDLGUILIB_API InputHandler
	{
	public:
		InputHandler();
		~InputHandler();
		SDL_Event& process(SDL_Event& e);

	private:
		std::vector<Window*> rootWindows;

		// helper functions
		static Event convertToSglEvent(SDL_Event& e);

		InputHandler& operator=(const InputHandler&) = delete;
		InputHandler(const InputHandler&) = delete;
	};

	namespace detail
	{
		extern InputHandler* globalInputHandlerInstance;
	}
}
