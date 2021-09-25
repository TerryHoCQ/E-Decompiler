#pragma once
#include <string>
#include <memory>

class SymbolInfo
{
	//µØÖ·
	uint64_t m_ea;
	//Ãû³Æ
	std::string m_name;
};

class IDASymbol
{
public:
	std::unique_ptr<SymbolInfo> find(uint64_t ea);
};