#pragma once

namespace sgl
{
	class Window;

	class IMessageBroker
	{
	public:
		virtual void registerWindow(Window& window) = 0;

		virtual ~IMessageBroker() = default;
	};
}