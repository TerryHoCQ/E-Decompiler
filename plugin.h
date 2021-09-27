#pragma once
#include <idp.hpp>
#include "GhidraDecompiler.h"

struct action_EmitGhidraPCode;
class Plugin :public plugmod_t
{
public:
	explicit Plugin(std::unique_ptr<GhidraDecompiler> decompiler);
	~Plugin();
	void view(const std::string& name, const DecompilerResult& code) const;
	void printPcode();
protected:
	virtual bool idaapi run(size_t) override;
private:
	std::unique_ptr<GhidraDecompiler> m_decompiler;
	action_EmitGhidraPCode* action_emitPCode;
};