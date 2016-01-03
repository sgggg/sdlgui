#include "stdafx.h"

#include "InputManager.h"

namespace sgl
{
	int GlobalInitialize()
	{
		if (detail::globalInputHandlerInstance == nullptr)
		{
			detail::globalInputHandlerInstance = new InputHandler();
		}
		return 0;
	}

	int GlobalCleanup()
	{
		delete detail::globalInputHandlerInstance;
		detail::globalInputHandlerInstance = nullptr;
		return 0;
	}

	void HandleInput(SDL_Event& e)
	{
		GetGlobalInputHandler().process(e);
	}

	InputHandler& GetGlobalInputHandler()
	{
		if (detail::globalInputHandlerInstance == nullptr)
		{
			// TODO error
		}
		return *detail::globalInputHandlerInstance;
	}

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

	Event InputHandler::convertToSglEvent(SDL_Event& e)
	{
		Event guiEvent;
		// TODO fill guiEvent with info from e 
		guiEvent.type = EventType::Button;
		return guiEvent;
	}
	
	namespace detail
	{
		InputHandler* globalInputHandlerInstance = nullptr;
	}
}
