#pragma once

#include "SDLGUILIB_API.h"
#include <functional>

namespace sgl
{
	struct Event;

	typedef std::function<void(const Event& e)> EventCallback;
	typedef int64_t EventTime;

	enum class EventType
	{
		ButtonPressed
	};
	
	struct Event
	{
		EventType type_;
		EventTime time_;
	};
}
