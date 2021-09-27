#include "exception.h"
#include <sstream>

Error::Error(std::string reason)
	: m_reason(reason)
{

}

char const* Error::what() const noexcept
{
	return m_reason.c_str();
}

UnImplementedFunction::UnImplementedFunction(const std::string& funcName)
	: Error("")
{
	std::stringstream ss(m_reason);
	ss << "Unimplemented function " << funcName;
	m_reason = ss.str();
}