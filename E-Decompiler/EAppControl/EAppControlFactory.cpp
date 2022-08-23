#include "EAppControlFactory.h"
#include "../ESymbol.h"
#include "../Utils/Common.h"
#include "CKrnl_window.h"
#include "CKrnl_EditBox.h"
#include "CKrnl_PicBox.h"
#include "CKrnl_ShapeBox.h"
#include "CKrnl_DrawPanel.h"
#include "CKrnl_Label.h"
#include "CKrnl_Button.h"
#include "CKrnl_GroupBox.h"
#include "CKrnl_CheckBox.h"
#include "CKrnl_ChkListBox.h"
#include "CKrnl_AnimateBox.h"
#include "CKrnl_RadioBox.h"
#include "CKrnl_ComboBox.h"
#include "CKrnl_ListBox.h"
#include "CKrnl_HScrollBar.h"
#include "CKrnl_VScrollBar.h"
#include "CKrnl_ProcessBar.h"
#include "CKrnl_SliderBar.h"
#include "CKrnl_Tab.h"
#include "CKrnl_Timer.h"

EAppControlFactory& EAppControlFactory::Instance()
{
	static EAppControlFactory instance;
	return instance;
}


void EAppControlFactory::RegisterEAppControl(std::string eControlLibInfo,unsigned int controlTypeId)
{
	//��Guid + �ؼ����� => �ؼ�����
	static std::map<std::string, fCreateEAppControl> tmpControlMap;
	if (!tmpControlMap.size()) {
		tmpControlMap["d09f2340818511d396f6aaf844c7e325����"] = fCreateEAppControl(CKrnl_window::create);
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325�˵�"] = fCreateEAppControl(CKrnl_Menu::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325�༭��"] = fCreateEAppControl(CKrnl_EditBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325ͼƬ��"] = fCreateEAppControl(CKrnl_PicBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325���ο�"] = fCreateEAppControl(CKrnl_ShapeBox::create);;
		tmpControlMap["d09f2340818511d396f6aaf844c7e325����"] = fCreateEAppControl(CKrnl_DrawPanel::create);;
		tmpControlMap["d09f2340818511d396f6aaf844c7e325�����"] = fCreateEAppControl(CKrnl_GroupBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325��ǩ"] = fCreateEAppControl(CKrnl_Label::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325��ť"] = fCreateEAppControl(CKrnl_Button::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325ѡ���"] = fCreateEAppControl(CKrnl_CheckBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325��ѡ��"] = fCreateEAppControl(CKrnl_RadioBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325��Ͽ�"] = fCreateEAppControl(CKrnl_ComboBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325�б��"] = fCreateEAppControl(CKrnl_ListBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325ѡ���б��"] = fCreateEAppControl(CKrnl_ChkListBox::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325���������"] = fCreateEAppControl(CKrnl_HScrollBar::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325���������"] = fCreateEAppControl(CKrnl_VScrollBar::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325������"] = fCreateEAppControl(CKrnl_ProcessBar::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325������"] = fCreateEAppControl(CKrnl_SliderBar::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325ѡ���"] = fCreateEAppControl(CKrnl_Tab::create);
		tmpControlMap["d09f2340818511d396f6aaf844c7e325Ӱ���"] = fCreateEAppControl(CKrnl_AnimateBox::create);
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325���ڿ�"] = krnl_DatePicker;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325����"] = krnl_MonthCalendar;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325��������"] = krnl_DriverBox;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325Ŀ¼��"] = krnl_DirBox;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325�ļ���"] = krnl_FileBox;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325��ɫѡ����"] = krnl_ColorPicker;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325����������"] = krnl_HyperLinker;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325������"] = krnl_Spin;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325ͨ�öԻ���"] = krnl_CommonDlg;
		tmpControlMap["d09f2340818511d396f6aaf844c7e325ʱ��"] = fCreateEAppControl(CKrnl_Timer::create);
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325��ӡ��"] = krnl_printer;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325���ݱ�"] = krnl_UDP;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325�ͻ�"] = krnl_Client;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325������"] = krnl_Server;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325�˿�"] = krnl_SerialPort;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325���"] = krnl_Grid;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325����Դ"] = krnl_DataSrc;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325ͨ���ṩ��"] = krnl_NProvider;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325���ݿ��ṩ��"] = krnl_DBProvider;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325ͼ�ΰ�ť"] = krnl_PicBtn;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325�ⲿ���ݿ�"] = krnl_ODBCDB;
		//tmpControlMap["d09f2340818511d396f6aaf844c7e325�ⲿ�����ṩ��"] = krnl_ODBCProvider;
		//tmpControlMap["{9DA96BF9CEBD45c5BFCF94CBE61671F5}�ϷŶ���"] = krnl_DropTarget;
	}

	std::map<std::string, fCreateEAppControl>::iterator it = tmpControlMap.find(eControlLibInfo);
	if (it != tmpControlMap.end()) {
		registerMap[controlTypeId] = it->second;
	}
	else {
		registerMap[controlTypeId] = fCreateEAppControl(EAppControl_Unknow::create);
	}
}

EAppControl* EAppControlFactory::CreateEAppControl(unsigned int dwControlTypeId)
{
	std::map<unsigned int, fCreateEAppControl>::iterator it = registerMap.find(dwControlTypeId);
	if (it == registerMap.end()) {
		return nullptr;
	}
	fCreateEAppControl fCreate = it->second;
	return (EAppControl*)fCreate();
}

EAppControl_Unknow* EAppControl_Unknow::create()
{
	return new EAppControl_Unknow();
}

std::string EAppControl_Unknow::GetEventName(int eventIndex)
{
	return "";
}

bool EAppControl_Unknow::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string EAppControl_Unknow::GetPropertyName(unsigned int propertyIndex)
{
	return "δ֪";
}
