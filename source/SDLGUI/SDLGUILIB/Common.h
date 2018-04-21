#pragma once

#include <cstdint>

namespace sgl
{
	class GuiManager;
	class Window;

	typedef std::int64_t WindowId;
	constexpr WindowId kInvalidWindowId = WindowId(-1);
}


