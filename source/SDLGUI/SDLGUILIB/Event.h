#pragma once

#include "SDLGUILIB_API.h"
#include <functional>

namespace sgl
{
	class Event;

	typedef std::function<void(const Event& e)> EventCallback;
	typedef int64_t EventTime;

	enum class EventType
	{
		Invalid,
		ButtonPressed,
		CheckBoxChecked,
		CheckBoxUnchecked
	};
	
	class Event
	{
	public:
		EventType type_ = EventType::Invalid;
		EventTime time_ = 0;
	};

	class CommandEvent : public Event
	{
	public:
		bool is_checked_ = false;
	};
}
