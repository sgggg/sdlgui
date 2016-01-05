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
}
