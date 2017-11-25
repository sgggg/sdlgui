#pragma once

#include "CppUnitTest.h"
#include "../SDLGUILIB/SGL.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework {
			template<> inline std::wstring ToString<sgl::EventType>(const sgl::EventType& q) { RETURN_WIDE_STRING(static_cast<int>(q)); }
		}
	}
}
