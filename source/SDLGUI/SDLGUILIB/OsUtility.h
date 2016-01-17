#pragma once

#include <string>

/**
 * This file contains functions with an operating system dependent implementation.
 */
namespace sgl
{
	/**
	 * @brief Returns the value of the environment variable with the given name.
	 * 
	 * @param variable Name of the environment variable to get.
	 * @return Value of the specified variable.
	 */
	std::string readEnvironmentVariable(const std::string& variable);

	enum class KnownFolders
	{
		Fonts
	};
	/**
	 * @brief Returns the path to the system folder spcified by the given parameter.
	 *
	 * @param folder The folder to get the path for.
	 * @return String containing the system path to the specified location.
	 */
	std::string getKnownFolderPath(KnownFolders folder);
}
