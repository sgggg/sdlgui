#pragma once

#include <functional>
#include <chrono>
#include <variant>

#include "SDLGUILIB_API.h"
#include "Common.h"

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
		Checked,
		Unchecked,
	};

	class Event
	{
	public:
		EventType type_ = EventType::Invalid;
		EventTime time_ = std::chrono::milliseconds(0);
		WindowId source_ = kInvalidWindowId;
		//std::variant<CommandEvent> event_payload_;
	};

	class CommandEvent : public Event
	{
	public:
		bool is_checked_ = false;
	};

	class SetFocusEvent : public Event
	{
	public:
		WindowId destination_ = kInvalidWindowId;
	};
}
