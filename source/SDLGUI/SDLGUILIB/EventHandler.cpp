#include "stdafx.h"

#include "EventHandler.h"

namespace sgl
{
	int GlobalInitialize()
	{
		if (detail::globalEventHandler == nullptr)
		{
			detail::globalEventHandler = new EventHandler();
		}
		return 0;
	}

	int GlobalCleanup()
	{
		delete detail::globalEventHandler;
		detail::globalEventHandler = nullptr;
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
		:rootWindows()
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
