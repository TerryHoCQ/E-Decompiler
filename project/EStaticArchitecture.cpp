#include "EStaticArchitecture.h"
#include "IDAWrapper.h"
#include "./DecompilerCore/ControlFlow.h"


ControlType_t GetControlType(std::string& controlInfo)
{
	//库Guid + 控件名称 => 控件类型
	static std::map<std::string, ControlType_t> ControlMap;
	if (!ControlMap.size()) {
		ControlMap["d09f2340818511d396f6aaf844c7e325窗口"] = krnl_window;
		ControlMap["d09f2340818511d396f6aaf844c7e325菜单"] = krnl_menu;
		ControlMap["d09f2340818511d396f6aaf844c7e325编辑框"] = krnl_EditBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325图片框"] = krnl_PicBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325外形框"] = krnl_ShapeBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325画板"] = krnl_DrawPanel;
		ControlMap["d09f2340818511d396f6aaf844c7e325分组框"] = krnl_GroupBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325标签"] = krnl_Label;
		ControlMap["d09f2340818511d396f6aaf844c7e325按钮"] = krnl_Button;
		ControlMap["d09f2340818511d396f6aaf844c7e325选择框"] = krnl_CheckBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325单选框"] = krnl_RadioBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325组合框"] = krnl_ComboBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325列表框"] = krnl_ListBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325选择列表框"] = krnl_ChkListBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325横向滚动条"] = krnl_HScrollBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325纵向滚动条"] = krnl_VScrollBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325进度条"] = krnl_ProcessBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325滑块条"] = krnl_SliderBar;
		ControlMap["d09f2340818511d396f6aaf844c7e325选择夹"] = krnl_Tab;
		ControlMap["d09f2340818511d396f6aaf844c7e325影像框"] = krnl_AnimateBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325日期框"] = krnl_DatePicker;
		ControlMap["d09f2340818511d396f6aaf844c7e325月历"] = krnl_MonthCalendar;
		ControlMap["d09f2340818511d396f6aaf844c7e325驱动器框"] = krnl_DriverBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325目录框"] = krnl_DirBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325文件框"] = krnl_FileBox;
		ControlMap["d09f2340818511d396f6aaf844c7e325颜色选择器"] = krnl_ColorPicker;
		ControlMap["d09f2340818511d396f6aaf844c7e325超级链接器"] = krnl_HyperLinker;
		ControlMap["d09f2340818511d396f6aaf844c7e325调节器"] = krnl_Spin;
		ControlMap["d09f2340818511d396f6aaf844c7e325通用对话框"] = krnl_CommonDlg;
		ControlMap["d09f2340818511d396f6aaf844c7e325时钟"] = krnl_Timer;
		ControlMap["d09f2340818511d396f6aaf844c7e325打印机"] = krnl_printer;
		ControlMap["d09f2340818511d396f6aaf844c7e325数据报"] = krnl_UDP;
		ControlMap["d09f2340818511d396f6aaf844c7e325客户"] = krnl_Client;
		ControlMap["d09f2340818511d396f6aaf844c7e325服务器"] = krnl_Server;
		ControlMap["d09f2340818511d396f6aaf844c7e325端口"] = krnl_SerialPort;
		ControlMap["d09f2340818511d396f6aaf844c7e325表格"] = krnl_Grid;
		ControlMap["d09f2340818511d396f6aaf844c7e325数据源"] = krnl_DataSrc;
		ControlMap["d09f2340818511d396f6aaf844c7e325通用提供者"] = krnl_NProvider;
		ControlMap["d09f2340818511d396f6aaf844c7e325数据库提供者"] = krnl_DBProvider;
		ControlMap["d09f2340818511d396f6aaf844c7e325图形按钮"] = krnl_PicBtn;
		ControlMap["d09f2340818511d396f6aaf844c7e325外部数据库"] = krnl_ODBCDB;
		ControlMap["d09f2340818511d396f6aaf844c7e325外部数据提供者"] = krnl_ODBCProvider;

		ControlMap["{9DA96BF9CEBD45c5BFCF94CBE61671F5}拖放对象"] = krnl_DropTarget;
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
//	show_wait_box(getUTF8String("扫描易语言函数").c_str());
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
//	show_wait_box(getUTF8String("解析易语言支持库信息").c_str());
//	ParseLibInfomation(eHead.lpLibEntry, eHead.dwLibNum);
//	hide_wait_box();
//
//	show_wait_box(getUTF8String("识别支持库函数").c_str());
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
	//		show_wait_box(getUTF8String("解析易语言常量资源").c_str());
	//		UserResourceParser::ParseUserResource(eHead.lpEString, eHead.dwEStringSize);
	//		hide_wait_box();
	//		ECSigParser::InitECSigResource(eHead.lpEString, eHead.lpEString + eHead.dwEStringSize);
	//		gMenu_ShowResource = IDAMenu::CreateMenu(getUTF8String("易语言/用户常量资源").c_str(), UserResourceParser::MenuHandle_ShowUserResource);
	//	}
	//
	//	if (eHead.lpEWindow != 0 && eHead.dwEWindowSize > 4) {
	//		show_wait_box(getUTF8String("解析易语言控件资源").c_str());
	//		GuiParser::ParseGUIResource(eHead.lpEWindow, eHead.dwEWindowSize);
	//		hide_wait_box();
	//		gMenu_ShowGUIInfo = IDAMenu::CreateMenu(getUTF8String("易语言/窗口控件信息").c_str(), GuiParser::MenuHandle_ShowGuiInfo);
	//		if (GuiParser::GetEventCount()) {
	//			gMenu_ShowEventInfo = IDAMenu::CreateMenu(getUTF8String("易语言/控件事件信息").c_str(), GuiParser::MenuHandle_ShowEventInfo);
	//		}
	//	}
	//
	//	if (eHead.dwApiCount) {
	//		show_wait_box(getUTF8String("解析易语言导入表").c_str());
	//		ImportsParser::ParseUserImports(eHead.dwApiCount, eHead.lpModuleName, eHead.lpApiName);
	//		hide_wait_box();
	//		gMenu_ShowGUIInfo = IDAMenu::CreateMenu(getUTF8String("易语言/用户导入表").c_str(), ImportsParser::MenuHandle_ShowImportsInfo);
	//	}
	//
	//#ifdef _DEBUG
	//	ECSigParser::Debug_outputECSig();
	//#endif
	//
	//	//识别易语言模块函数
	//	show_wait_box(getUTF8String("识别模块函数").c_str());
	//	qstring mainECpath;
	//	mainECpath.sprnt("%s\\esig\\精易模块.msig", idadir(PLG_SUBDIR));
	//	ECSigParser::ScanMSig(mainECpath.c_str(), m_eAppInfo.m_UserCodeStartAddr, m_eAppInfo.m_UserCodeEndAddr);
	//	hide_wait_box();
	//	msg("%s\n", getUTF8String("检测到是易语言静态编译程序").c_str());
	return true;
}

void EStaticArchitecture::performActions()
{
	//测试代码
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
		unsigned int krnl_MReportError;               //错误回调
		unsigned int krnl_MCallDllCmd;                //DLL命令
		unsigned int krnl_MCallLibCmd;                //三方支持库命令
		unsigned int krnl_MCallKrnlLibCmd;            //核心支持库命令
		unsigned int krnl_MReadProperty;              //读取组件属性
		unsigned int krnl_MWriteProperty;             //设置组件属性
		unsigned int krnl_MMalloc;                    //分配内存
		unsigned int krnl_MRealloc;                   //重新分配内存
		unsigned int krnl_MFree;                      //释放内存
		unsigned int krnl_MExitProcess;               //结束
		unsigned int krnl_MMessageLoop;               //窗口消息循环
		unsigned int krnl_MLoadBeginWin;              //载入启动窗口
		unsigned int krnl_MOtherHelp;                 //辅助功能
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

		//判断是否符合支持库格式
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
