#pragma once

#include "SDLGUILIB_API.h"
#include <functional>
#include <chrono>

namespace sgl
{
	class Event;

	typedef std::function<void(const Event& e)> EventCallback;
	typedef std::chrono::milliseconds EventTime;

	enum class EventType
	{
		Invalid,
		ButtonDown,
		ButtonUp,
		ButtonPressed,
		CheckBoxChecked,
		CheckBoxUnchecked,
		RadioButtonChecked,
		RadioButtonUnchecked,
	};
	
	class Event
	{
	public:
		EventType type_ = EventType::Invalid;
		EventTime time_ = std::chrono::milliseconds(0);
	};

	class CommandEvent : public Event
	{
	public:
		bool is_checked_ = false;
	};
}
