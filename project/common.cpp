#include "common.h"
#include <sstream>
#include <cstdint>
#include <stdarg.h>

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

std::string StringUtils::vsprintf(_In_z_ _Printf_format_string_ const char* format, va_list args)
{
	char sbuffer[64] = "";
	if (_vsnprintf_s(sbuffer, _TRUNCATE, format, args) != -1)
		return sbuffer;

	std::vector<char> buffer(256, '\0');
	while (true)
	{
		int res = _vsnprintf_s(buffer.data(), buffer.size(), _TRUNCATE, format, args);
		if (res == -1)
		{
			buffer.resize(buffer.size() * 2);
			continue;
		}
		else
			break;
	}
	return std::string(buffer.data());
}

std::string StringUtils::sprintf(_In_z_ _Printf_format_string_ const char* format, ...)
{
	va_list args;
	va_start(args, format);
	auto result = vsprintf(format, args);
	va_end(args);
	return result;
}
