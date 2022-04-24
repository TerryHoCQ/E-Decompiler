#include "plugin.h"
#include <hexrays.hpp>
#include "EDecompiler.h"
#include <kernwin.hpp>
#include "common/public.h"

// Hex-Rays API pointer
hexdsp_t* hexdsp = nullptr;

static int processor_id() {
#if IDA_SDK_VERSION < 750
	return ph.id;
#else
	return PH.id;
#endif
}

static ssize_t idaapi menu_callback(void* ud, int notification_code, va_list va)
{
	plugin_ctx_t* plgmod = (plugin_ctx_t*)ud;
	if (notification_code == ui_populating_widget_popup) {
		TWidget* view = va_arg(va, TWidget*);
		if (get_widget_type(view) == BWN_DISASM) {
			TPopupMenu* p = va_arg(va, TPopupMenu*);
			if (plgmod->bShowDecompile.load() == true) {
				attach_action_to_popup(view, p, plgmod->actionName_DoDecompile, nullptr, SETMENU_FIRST);
			}
		}
	}
	return 0;
}

static plugmod_t* idaapi init()
{
	if(!init_hexrays_plugin()) {
		return nullptr;
	}
	if (processor_id() != PLFM_386) {
		return nullptr;
	}
	msg("[E-Decompiler] plugin 1.0 loaded,Author: fjqisba\n");
	return new plugin_ctx_t;
}



plugin_ctx_t::plugin_ctx_t()
{
	//加载菜单视图
	hook_to_notification_point(HT_UI, menu_callback, this);

	//注册动作
	qstring actionName = getUTF8String("反编译易语言");
	const action_desc_t act_DoDecompile = ACTION_DESC_LITERAL_PLUGMOD(
		actionName_DoDecompile,
		actionName.c_str(),
		&this->actionHandler_DoDecompile,
		this,
		nullptr,
		nullptr,
		-1
	);
	register_action(act_DoDecompile);
}

plugin_ctx_t::~plugin_ctx_t()
{
	term_hexrays_plugin();
	unhook_from_notification_point(HT_UI, menu_callback);
}


int idaapi ActionDecompile::activate(action_activation_ctx_t* ctx)
{
	TWidget* currentViewer = get_current_viewer();
	if (!currentViewer) {
		return 1;
	}

	ea_t startAddr = get_screen_ea();
	EDecompilerEngine::Instance().DoDecompile(startAddr);

	return 1;
}

bool idaapi plugin_ctx_t::run(size_t)
{
	show_wait_box(getUTF8String("开始分析程序").c_str());
	bool inited = EDecompilerEngine::Instance().InitDecompiler(this);
	if (inited == false) {
		msg(getUTF8String("[E-Decompiler]分析易语言程序失败").c_str());
		hide_wait_box();
		return false;
	}
	hide_wait_box();
	this->bShowDecompile.store(true);

	/*auto func_address = get_screen_ea();
	auto decompilerResult = m_decompiler->decompile(func_address);
	if (!decompilerResult.cCode.empty())
	{
		view(decompilerResult.name, decompilerResult);
	}*/
	//
	//auto_wait();
	
	//if (!g_MyDecompiler.InitDecompilerEngine()) {
	//	msg("Error,InitDecompilerEngine Failed\n");
	//	return false;
	//}
	
	return true;

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
  "",                   // the preferred hotkey to run the plugin
};