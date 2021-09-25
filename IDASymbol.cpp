#include "IDASymbol.h"
#include <name.hpp>

std::unique_ptr<SymbolInfo> IDASymbol::find(uint64_t ea)
{
	qstring name;
	if (get_name(&name, ea) == 0 || name.size() == 0)
	{
		return nullptr;
	}
	return std::make_unique<SymbolInfo>(ea, name.c_str());
}