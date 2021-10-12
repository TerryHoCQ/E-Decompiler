#pragma once
#include <idp.hpp>
#include "GhidraDecompiler.h"
#include "common\public.h"

class Plugin;
struct ActHandler_EmitGhidraPCode :public action_handler_t
{
public:
	static qstring ActHandler_EmitGhidraPCode::actionName;
	static qstring ActHandler_EmitGhidraPCode::actionLabel;
	
	ActHandler_EmitGhidraPCode(GhidraDecompiler* d)
	{
		actionName = "E-Decompiler:GeneratePCode";
		actionLabel = getUTF8String("Éú³ÉGhidra P-code");
		decompiler = d;
	}
	int idaapi activate(action_activation_ctx_t* ctx)
	{
		if (!decompiler || !decompiler->m_architecture) {
			return 1;
		}
		TWidget* currentViewer = get_current_viewer();
		if (!currentViewer) {
			return 1;
		}
		ea_t StartEA = 0;
		ea_t EndEA;
		std::string result;
		if (!read_range_selection(currentViewer, &StartEA, &EndEA)) {
			StartEA = get_screen_ea();
			result = decompiler->GetPcode(StartEA, StartEA + 1);
		}
		else {
			result = decompiler->GetPcode(StartEA, EndEA);
		}

		msg(result.c_str());
		return 1;
	}
	action_state_t idaapi update(action_update_ctx_t* ctx)
	{
		return AST_ENABLE_ALWAYS;
	}
private:
	GhidraDecompiler* decompiler;
};

class Plugin :public plugmod_t
{
public:
	explicit Plugin(std::unique_ptr<GhidraDecompiler> decompiler);
	~Plugin();
	void view(const std::string& name, const DecompilerResult& code) const;
protected:
	virtual bool idaapi run(size_t) override;
private:
	std::unique_ptr<GhidraDecompiler> m_decompiler;

	ActHandler_EmitGhidraPCode actHandler_EmitGhidraPCode = ActHandler_EmitGhidraPCode(m_decompiler.get());
	const action_desc_t act_emitGhidraPCode_desc = ACTION_DESC_LITERAL_PLUGMOD(
		ActHandler_EmitGhidraPCode::actionName.c_str(),
		ActHandler_EmitGhidraPCode::actionLabel.c_str(),
		&actHandler_EmitGhidraPCode,
		this,
		nullptr,
		nullptr,
		-1
	);
};