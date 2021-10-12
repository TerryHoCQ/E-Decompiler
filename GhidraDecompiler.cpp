#include "GhidraDecompiler.h"
#include "Ghidra/funcdata.hh"
#include "IDAArchitecture.h"
#include "IDAWrapper.h"
#include "IDAPrint.h"
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

	if (decompiler->m_architecture) {
		try
		{
			DocumentStorage store;
			decompiler->m_architecture->init(store);
		}
		catch (Error& e)
		{
			return nullptr;
		}
	}

	return decompiler;
}

bool GhidraDecompiler::InitGhidraDecompiler()
{
	static bool bInited = false;
	if (!bInited) {
		CapabilityPoint::initializeAll();
		ArchitectureCapability::sortCapabilities();

		std::string idaDir = IDAWrapper::idadir("plugins");
		SleighArchitecture::scanForSleighDirectories(idaDir + "\\Ghidra");
		bInited = true;
	}
	return true;
}

DecompilerResult GhidraDecompiler::decompile(uint64_t funcAddress)
{
	DecompilerResult result;
	try
	{
		auto funcSym = m_architecture->getSymbolDatabase().find_function(funcAddress);

		if (!funcSym)
		{
			return result;
		}

		auto scope = m_architecture->symboltab->getGlobalScope();
		// clear scope to update all symbols
		//scope->clear();

		auto fd = scope->findFunction(Address(m_architecture->getDefaultCodeSpace(), funcSym->m_ea));

		m_architecture->clearAnalysis(fd);
		m_architecture->performActions(*fd);

		m_architecture->setPrintLanguage("e-language");

		stringstream ss;
		m_architecture->print->setIndentIncrement(3);
		m_architecture->print->setOutputStream(&ss);

		//print as C
		m_architecture->print->docFunction(fd);

		// get back context information
		auto idaPrint = static_cast<IDAPrint*>(m_architecture->print);
		return DecompilerResult(funcSym->m_name, funcSym->m_ea, ss.str(), idaPrint->getEmitter().getSymbolAddr());
	}
	catch (...) 
	{
		int a = 0;
	}

	return result;
}

std::string GhidraDecompiler::GetPcode(uint64_t start, uint64_t end)
{
	return m_architecture->emitPCode(start, end);
}