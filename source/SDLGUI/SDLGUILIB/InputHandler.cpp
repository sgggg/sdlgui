#include "stdafx.h"

#include "InputHandler.h"

namespace sgl
{
	InputHandler::InputHandler()
		:rootWindows()
	{
	}

	InputHandler::~InputHandler()
	{
	}

	SDL_Event& InputHandler::process(SDL_Event& e)
	{
		auto event = convertToSglEvent(e);
		switch (e.type)
		{
		case SDL_QUIT:
			break;
		default:
			break;
		}
		return e;
	}

	Event InputHandler::convertToSglEvent(SDL_Event& /*e*/)
	{
		Event guiEvent;
		// TODO fill guiEvent with info from e 
		guiEvent.type = EventType::Button;
		return guiEvent;
	}
}
