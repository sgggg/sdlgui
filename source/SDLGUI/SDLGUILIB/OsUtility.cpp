#include "stdafx.h"
#include "OsUtility.h"
#include "ErrorHandling.h"

#include "windows.h"
#include <objbase.h>			// provides CoTaskMemFree
#include <Shlobj.h>				// provides SHGetKnownFolderPath
#include <Knownfolders.h>		// provides FOLDERID_Fonts
#include <codecvt>				// this is used in convert_wide_to_narrow_string

namespace sgl
{
	std::string sgl::readEnvironmentVariable(const std::string& variable)
	{
#ifdef _WIN32
		constexpr auto buffer_size = 32767;	// see https://msdn.microsoft.com/en-us/library/windows/desktop/ms683188(v=vs.85).aspx
		auto buffer = std::unique_ptr<char[]>(new char[buffer_size]);
		const auto num_chars = GetEnvironmentVariableA(variable.c_str(), buffer.get(), buffer_size);
		if (num_chars == 0)
		{
			// TODO error
			return "";
		}
		return buffer.get();
#endif
	}

	std::string getKnownFolderPath(KnownFolders folder)
	{
#ifdef _WIN32
		wchar_t* folder_path = nullptr;
		switch (folder)
		{
		case KnownFolders::Fonts:
			SHGetKnownFolderPath(FOLDERID_Fonts, 0, NULL, &folder_path);
			break;
		default:
			// TODO error
			break;
		}
		auto path(utf8_encode(folder_path));
		CoTaskMemFree(folder_path);
		return path;
#endif
	}

	std::string utf8_encode(const std::wstring &wstr)
	{
#ifdef _WIN32
		if (wstr.empty())
		{
			return std::string();
		}
		auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);
		auto result = std::string(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), &result[0], size_needed, NULL, NULL);
		return result;
#endif
	}

	std::wstring utf8_decode(const std::string &str)
	{
#ifdef _WIN32
		if (str.empty())
		{
			return std::wstring();
		}
		auto size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), NULL, 0);
		auto result = std::wstring(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), &result[0], size_needed);
		return result;
#endif
	}
}
