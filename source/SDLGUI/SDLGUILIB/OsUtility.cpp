#include "stdafx.h"
#include "OsUtility.h"
#include "ErrorHandling.h"
#include "Utility.h"

#include "windows.h"
#include <objbase.h>			// provides CoTaskMemFree
#include <Shlobj.h>				// provides SHGetKnownFolderPath
#include <Knownfolders.h>		// provides FOLDERID_Fonts

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
	std::string getKnownFolderPath(KnownFolders folder)
	{
#ifdef _WIN32
		wchar_t* folderPath = nullptr;
		switch (folder)
		{
		case KnownFolders::Fonts:
			SHGetKnownFolderPath(FOLDERID_Fonts, 0, NULL, &folderPath);
			break;
		default:
			// TODO error
			break;
		}
		std::string path(ws2s(folderPath));
		CoTaskMemFree(folderPath);
		return path;
#endif
	}
}
