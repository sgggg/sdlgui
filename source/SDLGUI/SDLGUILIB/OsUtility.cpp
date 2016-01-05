#include "stdafx.h"
#include "OsUtility.h"
#include "ErrorHandling.h"

#include "windows.h"

namespace sgl
{
	std::string sgl::readEnvironmentVariable(const std::string& variable)
	{
#ifdef _WIN32
		auto bufSize = 32767;	// see https://msdn.microsoft.com/en-us/library/windows/desktop/ms683188(v=vs.85).aspx
		auto buffer = std::unique_ptr<char[]>(new char[bufSize]);
		auto numChars = GetEnvironmentVariableA(variable.c_str(), buffer.get(), bufSize);
		if (numChars == 0)
		{
			// TODO error
			return "";
		}
		return buffer.get();
#endif
	}
}
