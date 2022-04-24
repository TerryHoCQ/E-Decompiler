#include "GhidraDecompiler.h"
#include "IDAArchitecture.h"
#include "IDAWrapper.h"
#include "SectionManager.h"
#include "EObject_Include.h"
#include "EStaticArchitecture.h"
#include "exception.h"

GhidraDecompiler::GhidraDecompiler()
{

}

GhidraDecompiler::~GhidraDecompiler()
{
	
}

ArchType GhidraDecompiler::DetectArchitecture()
{
	unsigned int eMagicHead = SectionManager::SeachBin("50 64 89 25 00 00 00 00 81 EC AC 01 00 00 53 56 57");
	if (eMagicHead != -1) {
		unsigned int dwHeadAddr = IDAWrapper::get_dword(eMagicHead + 0x26);
		EStaticHead eHead;
		IDAWrapper::get_bytes(&eHead, sizeof(EStaticHead), dwHeadAddr);
		if (eHead.dwMagic == 0x3) {
			auto staticArch = std::make_unique<EStaticArchitecture>();
			if (staticArch->Parse_EStatic(dwHeadAddr)) {
				m_architecture = std::move(staticArch);
				return ESTATIC_ARCH;
			}
		}
	}

	//Ç¿ÖÆËÑË÷Ò×ÓïÑÔ¾²Ì¬±àÒëÌØÕ÷
	//To do...
	return UNKNOWN_ARCH;
}

std::unique_ptr<GhidraDecompiler> GhidraDecompiler::build()
{
	if (!GhidraDecompiler::InitGhidraDecompiler()) {
		return nullptr;
	}

	if (!SectionManager::InitSectionManager()) {
		return nullptr;
	}

	auto decompiler = std::make_unique<GhidraDecompiler>();
	
	//ÅÐ¶ÏÓïÑÔ
	ArchType type = decompiler->DetectArchitecture();
	if (type == UNKNOWN_ARCH) {
		return nullptr;
	}


	return decompiler;
}

bool GhidraDecompiler::InitGhidraDecompiler()
{
	return true;
}

DecompilerResult GhidraDecompiler::decompile(uint64_t funcAddress)
{
	DecompilerResult result;
	try
	{
		m_architecture->performActions();
	}
	catch (...)
	{
		int a = 0;
	}

	return result;
}

