#include "stdafx.h"

#include "EventHandler.h"

namespace sgl
{
	int GlobalInitialize()
	{
		detail::globalEventHandler = new EventHandler();
		return 0;
	}

	int GlobalCleanup()
	{
		delete detail::globalEventHandler;
		return 0;
	}

	void HandleEvent(SDL_Event& e)
	{
		if (detail::globalEventHandler == nullptr)
		{
			// TODO error
		}
		else
		{
			detail::globalEventHandler->process(e);
		}
	}

	EventHandler::EventHandler()
	{
	}

	EventHandler::~EventHandler()
	{
	}

	SDL_Event& EventHandler::process(SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			break;
		default:
			break;
		}
		return e;
	}

	namespace detail
	{
		EventHandler* globalEventHandler = nullptr;
	}
}
