#pragma once
#include <exception>
#include <string>

class Error :public std::exception
{
public:
	explicit Error(std::string reason);

	virtual char const* what() const noexcept override;
protected:
	std::string m_reason;

};

class UnImplementedFunction : public Error
{
public:
	explicit UnImplementedFunction(const std::string& funcName);
};