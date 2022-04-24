#pragma once
#include <vector>
#include <string>

std::vector<std::string> split(const std::string& s, char delimiter);

namespace StringUtils
{
	std::string sprintf(_In_z_ _Printf_format_string_ const char* format, ...);
	std::string vsprintf(_In_z_ _Printf_format_string_ const char* format, va_list args);
}

