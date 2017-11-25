#pragma once

#include "SDLGUILIB_API.h"
#include "SDL.h"

namespace sgl
{
	class SDLGUILIB_API EventProcessor
	{
	public:
		/**
		 * @brief Pass events to be handled by this event processor object to this function.
		 * @param e `SDL_Event` to be handled.
		 * @return `true` if this processor successfully handled the given event, 
		 * `false` otherwise.
		 */
		virtual bool handleEvent(const SDL_Event& e) = 0;
		virtual ~EventProcessor() = default;
	};
}
