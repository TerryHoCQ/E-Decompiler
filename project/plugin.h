#pragma once
#include <idp.hpp>
#include <atomic>

struct ActionDecompile :public action_handler_t
{
private:
	int idaapi ActionDecompile::activate(action_activation_ctx_t* ctx);
	action_state_t idaapi update(action_update_ctx_t* ctx)
	{
		return AST_ENABLE_ALWAYS;
	}
};

struct plugin_ctx_t : public plugmod_t
{
	plugin_ctx_t();
	~plugin_ctx_t();
	virtual bool idaapi run(size_t) override;
public:
	std::atomic<bool> bShowDecompile = false;
	const char* actionName_DoDecompile = "EDecompiler::DoDecompile";
	ActionDecompile actionHandler_DoDecompile;
};