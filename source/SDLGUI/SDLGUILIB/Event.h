#pragma once

#include "SDLGUILIB_API.h"
#include <functional>

namespace sgl
{
	class Event;

	typedef std::function<void(const Event& e)> EventCallback;

	enum class EventType
	{
		Button
	};
	
	enum class MouseState
	{
		LeftClick,
		LeftDoubleClick,
		RightClick,
		MiddleClick
	};

	class Event
	{
	public:
		EventType type;
	};
}
