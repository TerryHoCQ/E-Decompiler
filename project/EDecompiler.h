#pragma once
#include "plugin.h"
#include ".\DecompilerCore\DecompilerWrapper.h"

//
//
//enum EProgramsType_t
//{
//	E_UNKNOWN = 0,  //未知类型
//	E_DYNAMIC,      //动态编译程序
//	E_STATIC,       //静态编译程序
//};
//
//#pragma pack(push,1)
//
//struct EVENT_INFO
//{
//	uint32 m_lpszName;       //事件名称
//	uint32 m_lpszExplain;    //事件详细解释
//	uint32 m_dwState;        //事件特殊标志
//	int32  m_nArgCount;      //事件的参数数目
//	uint32 m_lpEventArgInfo; //参数
//};

//#pragma pack(pop)

//class IDAMenu;

class EDecompilerEngine:public DecompilerWrapper
{
public:
	EDecompilerEngine();
	~EDecompilerEngine();
public:
	static EDecompilerEngine& Instance();
	void DoDecompile(ea_t startAddr);
	bool InitDecompiler(plugin_ctx_t* ctx);
private:
	plugin_ctx_t* pluginCtx = nullptr;
//	//扫描易语言函数
//	void makeFunction(ea_t startAddr, ea_t endAddr);
//	bool InitDecompilerEngine();
//	
//	//根据菜单的类型ID来得到名称
//	static qstring GetControlTypeName(uint32 typeId);
//	static ssize_t ui_callback(void* ud, int notification_code, va_list va);
//private:
//	//扫描易语言基础库函数
//	void ScanEBasicLibFunc();
//	bool SetKrnlJmpAddr(ea_t callAddr, ea_t setAddr);
//public:
//	EProgramsType_t m_ProgramType;
//	mid_EAppInfo m_eAppInfo;
//private:
//	ea_t m_EHeadAddr;
//	IDAMenu* gMenu_ShowResource = nullptr;
//	IDAMenu* gMenu_ShowGUIInfo = nullptr;
//	IDAMenu* gMenu_ShowEventInfo = nullptr;
//	IDAMenu* gMenu_ShowImportsInfo = nullptr;
};

//extern EDecompilerEngine g_MyDecompiler;