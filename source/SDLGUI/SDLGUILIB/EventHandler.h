#pragma once

#include "SDL.h"
#include "SDLGUILIB_API.h"

namespace sgl
{
	SDLGUILIB_API int GlobalInitialize();
	SDLGUILIB_API int GlobalCleanup();
	SDLGUILIB_API void HandleEvent(SDL_Event& e);

	class EventHandler
	{
	public:
		EventHandler();
		~EventHandler();
		SDL_Event& process(SDL_Event& e);

	private:
		EventHandler& operator=(const EventHandler&) = delete;
		EventHandler(const EventHandler&) = delete;
	};

	namespace detail
	{
		extern EventHandler* globalEventHandler;
	}
}
