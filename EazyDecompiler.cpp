#include "EazyDecompiler.h"
#include "IDAArchitecture.h"

EazyDecompiler::EazyDecompiler(std::unique_ptr<IDAArchitecture> architecture):
	GhidraDecompiler(std::move(architecture))
{
	
}

std::unique_ptr<EazyDecompiler> EazyDecompiler::build()
{
	std::string target = "x86:LE:32:default";
	
	auto architecture = std::make_unique<IDAArchitecture>(target);

	architecture->addInjection("alloca_probe", "alloca_probe");
	architecture->addInjection("guard_dispatch_icall_fptr", "guard_dispatch_icall");

	try
	{
		DocumentStorage store;
		architecture->init(store);
		return std::make_unique<EazyDecompiler>(std::move(architecture));
	}
	catch (LowlevelError& e)
	{
		return nullptr;
	}
}