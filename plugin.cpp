#include "plugin.h"
#include <hexrays.hpp>
#include "EDecompiler.h"
#include "EazyDecompiler.h"
#include <sstream>
#include "common/public.h"

static int processor_id() {
#if IDA_SDK_VERSION < 750
	return ph.id;
#else
	return PH.id;
#endif
}

#define ACTION_GEN_PCODE "ghidra::pcode"

static void idaapi _Close(TWidget* cv, void* ud)
{
	auto code = static_cast<DecompilerResult*>(ud);
	delete code;
}

static const custom_viewer_handlers_t _ViewHandlers(
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	_Close,
	nullptr,
	nullptr
);

struct action_EmitGhidraPCode :public action_handler_t
{
	action_EmitGhidraPCode(Plugin* p)
	{
		plugin = p;
	}
	int idaapi activate(action_activation_ctx_t* ctx)
	{
		plugin->printPcode();
		return 1;
	}
	action_state_t idaapi update(action_update_ctx_t* ctx)
	{
		return AST_ENABLE_ALWAYS;
	}
private:
	Plugin* plugin;
};



Plugin::Plugin(std::unique_ptr<GhidraDecompiler> decompiler) :
	m_decompiler(std::move(decompiler))
{
	hook_to_notification_point(HT_UI, g_MyDecompiler.ui_callback);

	action_emitPCode = new action_EmitGhidraPCode(this);
	//添加生成PCode菜单
	qstring menuName = getUTF8String("生成Ghidra P-code");
	const action_desc_t act_GenPCode = { sizeof(action_desc_t),ACTION_GEN_PCODE,menuName.c_str(),
		action_emitPCode,this,nullptr,nullptr,0,ADF_OT_PLUGIN };

	register_action(act_GenPCode);

}

Plugin::~Plugin()
{
	term_hexrays_plugin();
	unhook_from_notification_point(HT_UI, g_MyDecompiler.ui_callback);
	if (action_emitPCode) {
		delete action_emitPCode;
		action_emitPCode = nullptr;
	}
}

void Plugin::printPcode()
{
	TWidget* currentViewer = get_current_viewer();
	if (!currentViewer) {
		return;
	}

	ea_t StartEA = 0;
	ea_t EndEA;
	std::string result;
	if (!read_range_selection(currentViewer, &StartEA, &EndEA)) {
		StartEA = get_screen_ea();
		result = m_decompiler->GetPcode(StartEA, StartEA + 1);
	}
	else {
		result = m_decompiler->GetPcode(StartEA, EndEA);
	}
	
	msg(result.c_str());
	int a = 0;
}

void Plugin::view(const std::string& name, const DecompilerResult& code)const
{
	strvec_t* sv = new strvec_t();
	std::istringstream iss(code.cCode);
	for (std::string line; std::getline(iss, line); )
	{
		sv->push_back(simpleline_t(line.c_str()));
	}

	simpleline_place_t s1;
	simpleline_place_t s2((int)(sv->size() - 1));
	auto oldWidget = find_widget(name.c_str());

	if (oldWidget != nullptr)
	{
		close_widget(oldWidget, 0);
	}

	auto w = create_custom_viewer(name.c_str(), &s1, &s2,
		&s1, nullptr, sv, &_ViewHandlers, new DecompilerResult(code));

	TWidget* code_view = create_code_viewer(w);
	set_code_viewer_is_source(code_view);
	display_widget(code_view, WOPN_DP_TAB);
}

bool idaapi Plugin::run(size_t)
{
	auto func_address = get_screen_ea();

	auto decompilerResult = m_decompiler->decompile(func_address);
	if (!decompilerResult.cCode.empty())
	{
		view(decompilerResult.name, decompilerResult);
	}

	//show_wait_box(getUTF8String("等待IDA初始化分析完毕").c_str());
	//auto_wait();
	//hide_wait_box();
	//
	//if (!g_MyDecompiler.InitDecompilerEngine()) {
	//	msg("Error,InitDecompilerEngine Failed\n");
	//	return false;
	//}

	return true;
}


// Hex-Rays API pointer
hexdsp_t* hexdsp = nullptr;

//--------------------------------------------------------------------------
static plugmod_t* idaapi init()
{
	if (!init_hexrays_plugin()) {
		return nullptr;
	}

	//To do...在这里判断是什么易语言
	if (processor_id() != PLFM_386) {
		return nullptr;
	}

	if (!GhidraDecompiler::InitGhidraDecompiler()) {
		return nullptr;
	}

	auto decompiler = EazyDecompiler::build();
	if (!decompiler) {
		return nullptr;
	}

	msg("[E-Decompiler] plugin 0.2 loaded,Author: fjqisba\n");
	return new Plugin(std::move(decompiler));
}

//--------------------------------------------------------------------------
static char comment[] = "E-Language Programs Decompiler By fjqisba";

#define PLUGINNAME "\xE6\x98\x93\xE8\xAF\xAD\xE8\xA8\x80\xE5\x8F\x8D\xE7\xBC\x96\xE8\xAF\x91\xE5\x99\xA8"

plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  PLUGIN_MULTI ,                // The plugin can work with multiple idbs in parallel
  init,                         // initialize
  nullptr,
  nullptr,
  comment,              // long comment about the plugin
  "fjqisba@sohu.com",   // multiline help about the plugin
  PLUGINNAME,           // the preferred short name of the plugin
  "F6",                 // the preferred hotkey to run the plugin
};
