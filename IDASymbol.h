#pragma once
#include <string>
#include <memory>

class SymbolInfo
{
	//��ַ
	uint64_t m_ea;
	//����
	std::string m_name;
};

class IDASymbol
{
public:
	std::unique_ptr<SymbolInfo> find(uint64_t ea);
};