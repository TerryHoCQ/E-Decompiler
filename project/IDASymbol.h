#pragma once
#include <string>
#include <memory>

//·ûºÅÐÅÏ¢
struct SymbolInfo
{
	uint64_t m_ea;
	std::string m_name;

	SymbolInfo(uint64_t ea, std::string name) :m_ea(ea), m_name(name)
	{

	}
};

class IDASymbol
{
public:
	std::unique_ptr<SymbolInfo> find(uint64_t ea);
	std::unique_ptr<SymbolInfo> find_function(uint64_t ea);
};