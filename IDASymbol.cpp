#include "IDASymbol.h"
#include <name.hpp>
#include <funcs.hpp>
#include "common.h"

std::unique_ptr<SymbolInfo> IDASymbol::find(uint64_t ea)
{
	qstring name;
	if (get_name(&name, ea) == 0 || name.size() == 0)
	{
		return nullptr;
	}
	return std::make_unique<SymbolInfo>(ea, name.c_str());
}

std::unique_ptr<SymbolInfo> IDASymbol::find_function(uint64_t ea)
{
	auto idaFunc = get_func(ea);
	if (idaFunc == nullptr)
	{
		return nullptr;
	}

	qstring idaName;
	get_short_name(&idaName, idaFunc->start_ea);
	auto beginParameter = idaName.find("(");
	auto functionName = split(idaName.substr(0, beginParameter).c_str(), ' ').back();

	return std::make_unique<SymbolInfo>(idaFunc->start_ea, functionName);
}