#pragma once
#include <pro.h>
#include "EAppControl/EAppControl.h"

class ControlInfoWidget;

class GuiParser
{
public:
	struct ControlIndex
	{
		unsigned int nWindowIndex;
		unsigned int nControlIndex;
	};
	struct mid_EventInfo
	{
		int m_nEventIndex;       //�¼�����
		uint32 m_EventAddr;      //�¼���ַ
	};

	//ÿ���ؼ����еĻ�������
	struct mid_EBasicProperty
	{
		int m_left;                              //���
		int m_top;                               //����
		int m_width;                             //���
		int m_height;                            //�߶�
		qvector<unsigned int> mVec_childControl; //�ӿؼ�
		qstring m_tag;                           //���
	};
	struct mid_ControlInfo
	{
		uint32 m_controlId;                      //�ؼ�����ID
		qstring m_controlName;                   //�ؼ�����
		uint32 m_controlTypeId;                  //�ؼ������������͵�ID
		qstring m_controlTypeName;               //�ؼ���������
		ea_t m_propertyAddr;                     //���Ե�ַ
		int32 m_propertySize;                    //���Դ�С
		qvector<mid_EventInfo> mVec_eventInfo;   //�¼�����
	};
	struct mid_GuiInfo
	{
		uint32 m_windowId;                           //�ؼ���������ID
		qvector<mid_ControlInfo> mVec_ControlInfo;   //�����еĿؼ�
	};
public:
	//��ȡ�ؼ��¼��ܸ���
	static unsigned int GetEventCount();
	static void InitUserCodeStartAddr(ea_t addr);
	static bool ParseGUIResource(ea_t lpGUIStart, uint32 infoSize);
	static int MenuHandle_ShowGuiInfo();
	static int MenuHandle_ShowEventInfo();

	//���ݿؼ�����ID����þ��������
	//static ControlType_t GetControlType(unsigned int controlTypeId);
	//���ݿؼ�IDֱ�ӻ�ȡ�ؼ�����
	//static bool GetControlInfo(unsigned int controlId, mid_ControlInfo& out_ControlInfo);

	//static void ClearControlTypeMap();
	//static void AddControlType(unsigned int, ControlType_t);
private:
	static void ParseControlBasciProperty(unsigned char* lpControlInfo, GuiParser::mid_ControlInfo& out_Property);
public:
	static ControlInfoWidget* g_ControlInfoWindow;
};