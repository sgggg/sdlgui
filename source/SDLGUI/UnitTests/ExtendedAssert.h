#pragma once

#include <cstdint>

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework {
			template<> inline std::wstring ToString<sgl::EventType>(const sgl::EventType& q)
			{
				RETURN_WIDE_STRING(static_cast<int>(q));
			}
			template<> inline std::wstring ToString<sgl::Point>(const sgl::Point& q)
			{
				RETURN_WIDE_STRING("(" << std::to_wstring(q.x) << "," << std::to_wstring(q.y) << ")");
			}
			template<> inline std::wstring ToString<sgl::Size>(const sgl::Size& q)
			{
				RETURN_WIDE_STRING("(" << std::to_wstring(q.width) << "," << std::to_wstring(q.height) << ")");
			}
			template<> inline std::wstring ToString<std::int64_t>(const std::int64_t& q)
			{
				RETURN_WIDE_STRING(q);
			}
		}
	}
}
