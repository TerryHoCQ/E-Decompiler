#pragma once
#include <idp.hpp>
#include "GhidraDecompiler.h"

class Plugin :public plugmod_t
{
public:
	explicit Plugin(std::unique_ptr<GhidraDecompiler> decompiler);
	~Plugin();
	virtual bool idaapi run(size_t) override;
private:
	std::unique_ptr<GhidraDecompiler> m_decompiler;
};