#include "plugin.h"
#include <hexrays.hpp>
#include "EDecompiler.h"
#include <sstream>
#include "common/public.h"

qstring ActHandler_EmitGhidraPCode::actionName;
qstring ActHandler_EmitGhidraPCode::actionLabel;

static int processor_id() {
#if IDA_SDK_VERSION < 750
	return ph.id;
#else
	return PH.id;
#endif
}

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


ssize_t menu_callback(void* ud, int notification_code, va_list va)
{
	if (notification_code == ui_populating_widget_popup) {
		TWidget* view = va_arg(va, TWidget*);
		if (get_widget_type(view) == BWN_DISASM) {
			TPopupMenu* p = va_arg(va, TPopupMenu*);
			//attach_action_to_popup(view, p, "eDecompiler::GenerateECSig", nullptr, SETMENU_FIRST);
			attach_action_to_popup(view, p, ActHandler_EmitGhidraPCode::actionName.c_str(), nullptr, SETMENU_FIRST);
		}
	}

	return 0;
}


Plugin::Plugin(std::unique_ptr<GhidraDecompiler> decompiler) :
	m_decompiler(std::move(decompiler))
{
	hook_to_notification_point(HT_UI, menu_callback);
	register_action(act_emitGhidraPCode_desc);
}

Plugin::~Plugin()
{
	term_hexrays_plugin();
	unhook_from_notification_point(HT_UI, menu_callback);
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

	if (processor_id() != PLFM_386) {
		return nullptr;
	}

	auto decompiler = GhidraDecompiler::build();
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
