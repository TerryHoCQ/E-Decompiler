#include "EDecompiler.h"
#include "DecompilerCore/FlowInfo.h"
#include "SectionManager.h"

//unsigned int GetDataTypeType(unsigned int typeID)
//{
//	unsigned int result = typeID;
//	if (typeID)
//	{
//		if ((typeID & 0xC0000000) == 0x80000000) {
//			result = 1;
//		}
//		else {
//			result = ((typeID & 0xC0000000) != 0x40000000) + 2;
//		}
//	}
//	return result;
//}

//qstring EDecompilerEngine::GetControlTypeName(uint32 typeId)
//{
//	qstring ret;
//	if (GetDataTypeType(typeId) != 3) {
//		return ret;
//	}
//
//	int libIndex = (typeId >> 0x10) - 1;
//	if (libIndex >= g_MyDecompiler.m_eAppInfo.mVec_LibInfo.size()) {
//		return ret;
//	}
//	int typeIndex = (unsigned short)typeId - 1;
//	if (typeIndex >= g_MyDecompiler.m_eAppInfo.mVec_LibInfo[libIndex].mVec_DataTypeInfo.size()) {
//		return ret;
//	}
//	ret = g_MyDecompiler.m_eAppInfo.mVec_LibInfo[libIndex].mVec_DataTypeInfo[typeIndex].m_Name;
//	return ret;
//}
//
//EDecompilerEngine::EDecompilerEngine()
//{
//	m_ProgramType = E_UNKNOWN;
//}
//
//EDecompilerEngine::~EDecompilerEngine()
//{
//	if (gMenu_ShowResource) {
//		gMenu_ShowResource->DestroyMenu();
//		gMenu_ShowResource = nullptr;
//	}
//	if (gMenu_ShowGUIInfo) {
//		gMenu_ShowGUIInfo->DestroyMenu();
//		gMenu_ShowGUIInfo = nullptr;
//	}
//	if (gMenu_ShowEventInfo) {
//		gMenu_ShowEventInfo->DestroyMenu();
//		gMenu_ShowEventInfo = nullptr;
//	}
//	if (gMenu_ShowImportsInfo) {
//		gMenu_ShowImportsInfo->DestroyMenu();
//		gMenu_ShowImportsInfo = nullptr;
//	}
//}
//


//bool EDecompilerEngine::SetKrnlJmpAddr(ea_t callAddr, ea_t setAddr)
//{
//	if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MReportError) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MReportError = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MCallDllCmd) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MCallDllCmd = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MCallLibCmd) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MCallLibCmd = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MCallKrnlLibCmd) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MCallKrnlLibCmd = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MReadProperty) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MReadProperty = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MWriteProperty) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MWriteProperty = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MMalloc) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MMalloc = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MRealloc) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MRealloc = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MFree) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MFree = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MExitProcess) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MExitProcess = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MMessageLoop) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MMessageLoop = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MLoadBeginWin) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MLoadBeginWin = setAddr;
//	}
//	else if (callAddr == m_eAppInfo.m_KrnlApp.krnl_MOtherHelp) {
//		m_eAppInfo.m_KrnlJmp.Jmp_MOtherHelp = setAddr;
//	}
//	else {
//		return false;
//	}
//	return true;
//}
//

EDecompilerEngine::EDecompilerEngine()
{

}

EDecompilerEngine::~EDecompilerEngine()
{

}

EDecompilerEngine& EDecompilerEngine::EDecompilerEngine::Instance()
{
	static EDecompilerEngine gInstance;
	return gInstance;
}

void EDecompilerEngine::DoDecompile(ea_t startAddr)
{
	auto funcData = this->decompile(startAddr);




	int a = 0;
}

//
//void EDecompilerEngine::ScanEBasicLibFunc()
//{
//	ESigScanner::ScanBasicFunction();
//}
//
//

bool EDecompilerEngine::InitDecompiler(plugin_ctx_t* ctx)
{
	this->pluginCtx = ctx;

	if (SectionManager::InitSectionManager() == false) {
		return false;
	}

	if (this->InitDecompilerWrapper() == false) {
		return false;
	}


	return true;
}
