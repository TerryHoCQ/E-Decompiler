#pragma once
#include "plugin.h"
#include ".\DecompilerCore\DecompilerWrapper.h"

//
//
//enum EProgramsType_t
//{
//	E_UNKNOWN = 0,  //δ֪����
//	E_DYNAMIC,      //��̬�������
//	E_STATIC,       //��̬�������
//};
//
//#pragma pack(push,1)
//
//struct EVENT_INFO
//{
//	uint32 m_lpszName;       //�¼�����
//	uint32 m_lpszExplain;    //�¼���ϸ����
//	uint32 m_dwState;        //�¼������־
//	int32  m_nArgCount;      //�¼��Ĳ�����Ŀ
//	uint32 m_lpEventArgInfo; //����
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
//	//ɨ�������Ժ���
//	void makeFunction(ea_t startAddr, ea_t endAddr);
//	bool InitDecompilerEngine();
//	
//	//���ݲ˵�������ID���õ�����
//	static qstring GetControlTypeName(uint32 typeId);
//	static ssize_t ui_callback(void* ud, int notification_code, va_list va);
//private:
//	//ɨ�������Ի����⺯��
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