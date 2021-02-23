#include <hexrays.hpp>
#include <auto.hpp>
#include "SectionManager.h"
#include "EsigLoader.h"
#include "EDecompiler.h"

 // Hex-Rays API pointer
hexdsp_t* hexdsp = nullptr;

//--------------------------------------------------------------------------
struct plugin_ctx_t : public plugmod_t
{
    bool inited = true;

    ~plugin_ctx_t()
    {
        if (inited)
            term_hexrays_plugin();
    }
    virtual bool idaapi run(size_t) override;
};

//--------------------------------------------------------------------------
static plugmod_t* idaapi init()
{
    if (!init_hexrays_plugin())
        return nullptr; // no decompiler
    const char* hxver = get_hexrays_version();
    return new plugin_ctx_t;
}



//--------------------------------------------------------------------------
bool idaapi plugin_ctx_t::run(size_t)
{
	if (!auto_is_ok() && ask_yn(0, "The autoanalysis has not finished yet.\nDo you want to continue?") < 1)
	{
		return true;
	}
    InitSectionManager();

    EDecompilerEngine eDecompiler;
    eDecompiler.DoDecompiler();

    qstring sigPath = ChooseEsig();
    if (sigPath.empty()) {
        return true;
    }
    
    if (!ApplyEsig(sigPath)) {
        return true;
    }


    return true;
}

//--------------------------------------------------------------------------
static char comment[] = "E-Language Programs Decompiler By fjqisba";


plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  PLUGIN_MULTI,         // The plugin can work with multiple idbs in parallel
  init,                 // initialize
  nullptr,
  nullptr,
  comment,              // long comment about the plugin
  "fjqisba@sohu.com",   // multiline help about the plugin
  "E-Decompiler",       // the preferred short name of the plugin
  nullptr,              // the preferred hotkey to run the plugin
};