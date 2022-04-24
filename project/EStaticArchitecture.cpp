#include "EStaticArchitecture.h"
#include "IDAWrapper.h"
#include "./DecompilerCore/ControlFlow.h"


ControlType_t GetControlType(std::string& controlInfo)
{
	//��Guid + �ؼ����� => �ؼ�����
	static std::map<std::string, ControlType_t> ControlMap;
	if (!ControlMap.size()) {
		ControlMap["d09f2340818511d396f6aaf844c7e325����"] = krnl_window;
		ControlMap["d09f2340818511d396f6aaf844c7e325�˵�"] = krnl_menu;
		ControlMap["d09f2340818511d396f6aaf844c7e325�༭��"] = krnl_EditBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325ͼƬ��"] = krnl_PicBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325���ο�"] = krnl_ShapeBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325����"] = krnl_DrawPanel;
		ControlMap["d09f2340818511d396f6aaf844c7e325�����"] = krnl_GroupBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325��ǩ"] = krnl_Label;
		ControlMap["d09f2340818511d396f6aaf844c7e325��ť"] = krnl_Button;
		ControlMap["d09f2340818511d396f6aaf844c7e325ѡ���"] = krnl_CheckBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325��ѡ��"] = krnl_RadioBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325��Ͽ�"] = krnl_ComboBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325�б��"] = krnl_ListBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325ѡ���б��"] = krnl_ChkListBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325���������"] = krnl_HScrollBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325���������"] = krnl_VScrollBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325������"] = krnl_ProcessBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325������"] = krnl_SliderBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325ѡ���"] = krnl_Tab;
		ControlMap["d09f2340818511d396f6aaf844c7e325Ӱ���"] = krnl_AnimateBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325���ڿ�"] = krnl_DatePicker;
		ControlMap["d09f2340818511d396f6aaf844c7e325����"] = krnl_MonthCalendar;
		ControlMap["d09f2340818511d396f6aaf844c7e325��������"] = krnl_DriverBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325Ŀ¼��"] = krnl_DirBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325�ļ���"] = krnl_FileBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325��ɫѡ����"] = krnl_ColorPicker;
		ControlMap["d09f2340818511d396f6aaf844c7e325����������"] = krnl_HyperLinker;
		ControlMap["d09f2340818511d396f6aaf844c7e325������"] = krnl_Spin;
		ControlMap["d09f2340818511d396f6aaf844c7e325ͨ�öԻ���"] = krnl_CommonDlg;
		ControlMap["d09f2340818511d396f6aaf844c7e325ʱ��"] = krnl_Timer;
		ControlMap["d09f2340818511d396f6aaf844c7e325��ӡ��"] = krnl_printer;
		ControlMap["d09f2340818511d396f6aaf844c7e325���ݱ�"] = krnl_UDP;
		ControlMap["d09f2340818511d396f6aaf844c7e325�ͻ�"] = krnl_Client;
		ControlMap["d09f2340818511d396f6aaf844c7e325������"] = krnl_Server;
		ControlMap["d09f2340818511d396f6aaf844c7e325�˿�"] = krnl_SerialPort;
		ControlMap["d09f2340818511d396f6aaf844c7e325���"] = krnl_Grid;
		ControlMap["d09f2340818511d396f6aaf844c7e325����Դ"] = krnl_DataSrc;
		ControlMap["d09f2340818511d396f6aaf844c7e325ͨ���ṩ��"] = krnl_NProvider;
		ControlMap["d09f2340818511d396f6aaf844c7e325���ݿ��ṩ��"] = krnl_DBProvider;
		ControlMap["d09f2340818511d396f6aaf844c7e325ͼ�ΰ�ť"] = krnl_PicBtn;
		ControlMap["d09f2340818511d396f6aaf844c7e325�ⲿ���ݿ�"] = krnl_ODBCDB;
		ControlMap["d09f2340818511d396f6aaf844c7e325�ⲿ�����ṩ��"] = krnl_ODBCProvider;

		ControlMap["{9DA96BF9CEBD45c5BFCF94CBE61671F5}�ϷŶ���"] = krnl_DropTarget;
	}

	return ControlMap[controlInfo];
}


EStaticArchitecture::EStaticArchitecture()
{
	//x86:LE:32:default
}

EStaticArchitecture::~EStaticArchitecture()
{

}

bool EStaticArchitecture::Parse_EStatic(unsigned int eHeadAddr)
{
	EStaticHead eHead;
	IDAWrapper::get_bytes(&eHead, sizeof(EStaticHead), eHeadAddr);
	if (eHead.dwMagic != 0x3) {
		return false;
	}

	if (!ParseLibInfomation(eHead.lpLibEntry, eHead.dwLibNum)) {
		return false;
	}

	//m_eAppInfo.m_UserCodeStartAddr = eHead.lpStartCode;
	//m_eAppInfo.m_UserCodeEndAddr = m_EHeadAddr;
//
//	show_wait_box(getUTF8String("ɨ�������Ժ���").c_str());
//	makeFunction(m_eAppInfo.m_UserCodeStartAddr, m_eAppInfo.m_UserCodeEndAddr);
//	auto_wait();
//	GuiParser::InitUserCodeStartAddr(m_eAppInfo.m_UserCodeStartAddr);
//	UserResourceParser::InitUserCodeAddr(m_eAppInfo.m_UserCodeStartAddr, m_eAppInfo.m_UserCodeEndAddr);
//	hide_wait_box();
//
//	if (!eHead.dwLibNum || !eHead.lpLibEntry) {
//		return false;
//	}
//
//	show_wait_box(getUTF8String("����������֧�ֿ���Ϣ").c_str());
//	ParseLibInfomation(eHead.lpLibEntry, eHead.dwLibNum);
//	hide_wait_box();
//
//	show_wait_box(getUTF8String("ʶ��֧�ֿ⺯��").c_str());
//	ESigScanner::ScanLibFunction(eHead.lpLibEntry, eHead.dwLibNum);
//	ScanEBasicLibFunc();
//	hide_wait_box();
//
	unsigned int dwKrnlEntry = eHead.lpEString;
	if (dwKrnlEntry == 0) {
		dwKrnlEntry = eHead.lpEWindow;
	}

	if (!ParseKrnlInterface(dwKrnlEntry)) {
		return false;
	}
	
	//	if (eHead.lpEString != 0 && eHead.dwEStringSize != 0) {
	//		show_wait_box(getUTF8String("���������Գ�����Դ").c_str());
	//		UserResourceParser::ParseUserResource(eHead.lpEString, eHead.dwEStringSize);
	//		hide_wait_box();
	//		ECSigParser::InitECSigResource(eHead.lpEString, eHead.lpEString + eHead.dwEStringSize);
	//		gMenu_ShowResource = IDAMenu::CreateMenu(getUTF8String("������/�û�������Դ").c_str(), UserResourceParser::MenuHandle_ShowUserResource);
	//	}
	//
	//	if (eHead.lpEWindow != 0 && eHead.dwEWindowSize > 4) {
	//		show_wait_box(getUTF8String("���������Կؼ���Դ").c_str());
	//		GuiParser::ParseGUIResource(eHead.lpEWindow, eHead.dwEWindowSize);
	//		hide_wait_box();
	//		gMenu_ShowGUIInfo = IDAMenu::CreateMenu(getUTF8String("������/���ڿؼ���Ϣ").c_str(), GuiParser::MenuHandle_ShowGuiInfo);
	//		if (GuiParser::GetEventCount()) {
	//			gMenu_ShowEventInfo = IDAMenu::CreateMenu(getUTF8String("������/�ؼ��¼���Ϣ").c_str(), GuiParser::MenuHandle_ShowEventInfo);
	//		}
	//	}
	//
	//	if (eHead.dwApiCount) {
	//		show_wait_box(getUTF8String("���������Ե����").c_str());
	//		ImportsParser::ParseUserImports(eHead.dwApiCount, eHead.lpModuleName, eHead.lpApiName);
	//		hide_wait_box();
	//		gMenu_ShowGUIInfo = IDAMenu::CreateMenu(getUTF8String("������/�û������").c_str(), ImportsParser::MenuHandle_ShowImportsInfo);
	//	}
	//
	//#ifdef _DEBUG
	//	ECSigParser::Debug_outputECSig();
	//#endif
	//
	//	//ʶ��������ģ�麯��
	//	show_wait_box(getUTF8String("ʶ��ģ�麯��").c_str());
	//	qstring mainECpath;
	//	mainECpath.sprnt("%s\\esig\\����ģ��.msig", idadir(PLG_SUBDIR));
	//	ECSigParser::ScanMSig(mainECpath.c_str(), m_eAppInfo.m_UserCodeStartAddr, m_eAppInfo.m_UserCodeEndAddr);
	//	hide_wait_box();
	//	msg("%s\n", getUTF8String("��⵽�������Ծ�̬�������").c_str());
	return true;
}

void EStaticArchitecture::performActions()
{
	//���Դ���
	unsigned int currentAddr = IDAWrapper::get_screen_ea();
	//OxFFDecompiler::ControlFlow TestFlow(currentAddr);
	//TestFlow.followFlow();
	
	//TestFlow.showGraph();

	return;
}

bool EStaticArchitecture::ParseKrnlInterface(unsigned int lpKrnlEntry)
{
	struct mid_KrnlApp
	{
		unsigned int krnl_MReportError;               //����ص�
		unsigned int krnl_MCallDllCmd;                //DLL����
		unsigned int krnl_MCallLibCmd;                //����֧�ֿ�����
		unsigned int krnl_MCallKrnlLibCmd;            //����֧�ֿ�����
		unsigned int krnl_MReadProperty;              //��ȡ�������
		unsigned int krnl_MWriteProperty;             //�����������
		unsigned int krnl_MMalloc;                    //�����ڴ�
		unsigned int krnl_MRealloc;                   //���·����ڴ�
		unsigned int krnl_MFree;                      //�ͷ��ڴ�
		unsigned int krnl_MExitProcess;               //����
		unsigned int krnl_MMessageLoop;               //������Ϣѭ��
		unsigned int krnl_MLoadBeginWin;              //������������
		unsigned int krnl_MOtherHelp;                 //��������
	};

	mid_KrnlApp tmpKrnlApp;
	lpKrnlEntry -= sizeof(mid_KrnlApp);
	IDAWrapper::get_bytes(&tmpKrnlApp, sizeof(mid_KrnlApp), lpKrnlEntry);


	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MReportError] = E_MReportError;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MCallDllCmd] = E_MCallDllCmd;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MCallLibCmd] = E_MCallLibCmd;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MCallKrnlLibCmd] = E_MCallKrnlLibCmd;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MReadProperty] = E_MReadProperty;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MWriteProperty] = E_MWriteProperty;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MMalloc] = E_MMalloc;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MRealloc] = E_MRealloc;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MFree] = E_MFree;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MExitProcess] = E_MExitProcess;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MMessageLoop] = E_MMessageLoop;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MLoadBeginWin] = E_MLoadBeginWin;
	m_KernelLib.map_KernelCall[tmpKrnlApp.krnl_MOtherHelp] = E_MOtherHelp;
	return true;
}



bool EStaticArchitecture::ParseLibInfomation(unsigned int lpLibStartAddr, unsigned int dwLibCount)
{
	for (unsigned int nLibIndex = 0; nLibIndex < dwLibCount; ++nLibIndex) {
		unsigned int controlTypeId = 0;
		LIB_INFO tmpLibInfo;
		IDAWrapper::get_bytes(&tmpLibInfo, sizeof(LIB_INFO), IDAWrapper::get_dword(lpLibStartAddr));
		lpLibStartAddr = lpLibStartAddr + 4;

		//�ж��Ƿ����֧�ֿ��ʽ
		if (tmpLibInfo.m_dwLibFormatVer != 0x1312D65) {
			continue;
		}

		mid_ELibInfo eLibInfo;
		eLibInfo.m_Name = IDAWrapper::get_shortstring(tmpLibInfo.m_lpName);
		eLibInfo.m_Guid = IDAWrapper::get_shortstring(tmpLibInfo.m_lpGuid);
		eLibInfo.m_nMajorVersion = tmpLibInfo.m_nMajorVersion;
		eLibInfo.m_nMinorVersion = tmpLibInfo.m_nMinorVersion;

		unsigned int lpFirstDataType = tmpLibInfo.m_lpDataType;
		for (int nDataTypeIndex = 0; nDataTypeIndex < tmpLibInfo.m_nDataTypeCount; ++nDataTypeIndex) {
			LIB_DATA_TYPE_INFO tmpDataTypeInfo;
			IDAWrapper::get_bytes(&tmpDataTypeInfo, sizeof(LIB_DATA_TYPE_INFO), lpFirstDataType);
			lpFirstDataType += sizeof(LIB_DATA_TYPE_INFO);
			if (tmpDataTypeInfo.m_lpszName) {
				controlTypeId = (nLibIndex + 1) << 0x10;
				controlTypeId = controlTypeId + (nDataTypeIndex + 1);
				std::string controlTypeName = IDAWrapper::get_shortstring(tmpDataTypeInfo.m_lpszName);
				m_ControlMapping[controlTypeId] = GetControlType(eLibInfo.m_Guid + controlTypeName);
			}
		}
		m_eAppInfo.mVec_LibInfo.push_back(eLibInfo);
	}

	return true;
}
