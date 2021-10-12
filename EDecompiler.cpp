//#include "EDecompiler.h"
//#include <bytes.hpp>
//#include <segment.hpp>
//#include <loader.hpp>
//#include <funcs.hpp>
//#include <typeinf.hpp>
//#include <ua.hpp>
//#include <auto.hpp>
//#include <allins.hpp>
//#include <diskio.hpp>
//#include "common/IDAMenu.h"
//#include "common/public.h"
//#include "ControlInfoWidget.h"
//#include "UserResourceParser.h"
//#include "GuiParser.h"
//#include "EsigScanner.h"
//#include "ECSigParser.h"
//#include "ImportsParser.h"
//#include "GhidraDecompiler.h"
//
//EDecompilerEngine g_MyDecompiler;
//
//#define ACTION_GenECSig "eDecompiler::GenerateECSig"
//
//struct GenECSigHandler :public action_handler_t
//{
//	int idaapi activate(action_activation_ctx_t* ctx)
//	{
//		return ECSigParser::GenerateECSig(get_screen_ea());
//	}
//	action_state_t idaapi update(action_update_ctx_t* ctx)
//	{
//		return AST_ENABLE_ALWAYS;
//	}
//};
//
//struct DecompileHandler :public action_handler_t
//{
//	int idaapi activate(action_activation_ctx_t* ctx)
//	{
//		return g_MyDecompiler.DoDecompile();
//	}
//	action_state_t idaapi update(action_update_ctx_t* ctx)
//	{
//		return AST_ENABLE_ALWAYS;
//	}
//};
//
//DecompileHandler gHandler_Decompile;
//GenECSigHandler gHandler_GenEcSig;
//
//
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
//
//
//void EDecompilerEngine::makeFunction(ea_t startAddr, ea_t endAddr)
//{
//	compiled_binpat_vec_t FuncHeadBin;
//	parse_binpat_str(&FuncHeadBin, 0, "55 8B EC", 16);
//
//	while (true)
//	{
//		startAddr = bin_search2(startAddr, endAddr, FuncHeadBin, 0x0);
//		if (startAddr == BADADDR)
//		{
//			break;
//		}
//		add_func(startAddr);
//		startAddr = startAddr + 3;
//	}
//}
//
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

//
//bool EDecompilerEngine::InitDecompilerEngine()
//{
//	
//	//注册窗口菜单
//	qstring menuName = getUTF8String("生成易语言函数特征");
//	const action_desc_t GenEsigDesc = {
//	sizeof(action_desc_t),
//	ACTION_GenECSig,
//	menuName.c_str(),
//	&gHandler_GenEcSig,
//	&PLUGIN,
//	nullptr,
//	nullptr,
//	0,
//	ADF_OT_PLUGIN
//	};
//	register_action(GenEsigDesc);
//
//	//注册快捷键
//	const action_desc_t desc = {
//	sizeof(action_desc_t),
//	"eDecompile",
//	"e Decompile",
//	&gHandler_Decompile,
//	&PLUGIN,
//	"F6",
//	nullptr,
//	0,
//	ADF_OT_PLUGIN
//	};
//	register_action(desc);
//	return true;
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

//
//void EDecompilerEngine::ScanEBasicLibFunc()
//{
//	ESigScanner::ScanBasicFunction();
//}
//
//
