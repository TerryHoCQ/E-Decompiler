#include "GhidraDecompiler.h"
#include "Ghidra/funcdata.hh"
#include "IDAArchitecture.h"
#include "IDAWrapper.h"
#include "IDAPrint.h"

GhidraDecompiler::GhidraDecompiler(std::unique_ptr<IDAArchitecture> arch) :
	m_architecture(std::move(arch))
{

}

bool GhidraDecompiler::InitGhidraDecompiler()
{
	CapabilityPoint::initializeAll();
	ArchitectureCapability::sortCapabilities();

	std::string idaDir = IDAWrapper::idadir("plugins");
	SleighArchitecture::scanForSleighDirectories(idaDir + "\\Ghidra");

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

bool GhidraDecompiler::LoadFile()
{
	//std::string fileName;
	//std::string target = "x86:LE:32:default";
	//
	//arch = new ECatArchitecture(fileName, target);
	//DocumentStorage store;
	//arch->init(store);



	return true;
}

bool GhidraDecompiler::DoDecompilerWork(unsigned int addr)
{
	//Address funcEntry(arch->getDefaultCodeSpace(), addr);
	////Funcdata* fd = GhidraDecompiler::Instance().arch->symboltab->getGlobalScope()->queryFunction(funcEntry);
	//if (fd == NULL) {
	//	//To do...
	//	std::string funcName = "func_test";
	//	//fd = GhidraWrapper::Instance().arch->symboltab->getGlobalScope()->addFunction(funcEntry, funcName)->getFunction();
	//	if (fd == NULL) {
	//		return false;
	//	}
	//}
	//
	//if (fd->hasNoCode()) {
	//	return false;
	//}
	//
	//if (fd->isProcStarted()) {
	//	return false;
	//}

	//arch->allacts.getCurrent()->reset(*fd);
	//int res = arch->allacts.getCurrent()->perform(*fd);
	//if (res < 0) {
	//	return false;
	//}
	//
	//std::stringstream decompileResult;
	//arch->print->setOutputStream(&decompileResult);
	//arch->print->docFunction(fd);
	//
	//std::string test = decompileResult.str();
	//
	//CustomCodeViewer* pCustomCodeViewer = new CustomCodeViewer();
	//IDAWrapper::display_widget(pCustomCodeViewer, 0x400004);



	return 0;

	return true;
}