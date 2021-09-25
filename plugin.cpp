#include "plugin.h"
#include <hexrays.hpp>
#include "EDecompiler.h"
#include "EazyDecompiler.h"

static int processor_id() {
#if IDA_SDK_VERSION < 750
	return ph.id;
#else
	return PH.id;
#endif
}

Plugin::Plugin(std::unique_ptr<GhidraDecompiler> decompiler) :
	m_decompiler(std::move(decompiler))
{
	hook_to_notification_point(HT_UI, g_MyDecompiler.ui_callback);
}

Plugin::~Plugin()
{
	term_hexrays_plugin();
	unhook_from_notification_point(HT_UI, g_MyDecompiler.ui_callback);
}

bool idaapi Plugin::run(size_t)
{
	auto func_address = get_screen_ea();



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

	GhidraDecompiler::InitGhidraDecompiler();
	auto decompiler = EazyDecompiler::build();
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
