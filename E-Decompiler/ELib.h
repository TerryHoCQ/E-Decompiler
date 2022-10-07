#pragma once

struct eSymbol_EventInfo
{
	int eventIndex;          //�¼�����
	unsigned int eventAddr;  //�¼���ַ
};

struct eSymbol_ImportsApi
{
	std::string libName;
	std::string apiName;
};

enum eSymbol_ControlType
{
	UnknownControl = 0,
	krnl_window,     //����
	krnl_menu,       //�˵�
	krnl_EditBox,    //�༭��
	krnl_PicBox,     //ͼƬ��
	krnl_ShapeBox,   //���ο�
	krnl_DrawPanel,  //����
	krnl_GroupBox,   //�����
	krnl_Label,      //��ǩ
	krnl_Button,     //��ť
	krnl_CheckBox,   //ѡ���
	krnl_RadioBox,   //��ѡ��
	krnl_ComboBox,   //��Ͽ�
	krnl_ListBox,    //�б��
	krnl_ChkListBox, //ѡ���б��
	krnl_HScrollBar, //���������
	krnl_VScrollBar, //���������
	krnl_ProcessBar, //������
	krnl_SliderBar,  //������
	krnl_Tab,        //ѡ���
	krnl_AnimateBox, //Ӱ���
	krnl_DatePicker, //���ڿ�
	krnl_MonthCalendar,  //����
	krnl_DriverBox,  //��������
	krnl_DirBox,     //Ŀ¼��
	krnl_FileBox,    //�ļ���
	krnl_ColorPicker, //��ɫѡ����
	krnl_HyperLinker, //����������
	krnl_Spin,        //������
	krnl_CommonDlg,   //ͨ�öԻ���
	krnl_Timer,       //ʱ��
	krnl_printer,     //��ӡ��
	krnl_UDP,         //���ݱ�
	krnl_Client,      //�ͻ�
	krnl_Server,      //������
	krnl_SerialPort,  //�˿�
	krnl_Grid,        //���
	krnl_DataSrc,     //����Դ
	krnl_NProvider,   //ͨ���ṩ��
	krnl_DBProvider,  //���ݿ��ṩ��
	krnl_PicBtn,      //ͼ�ΰ�ť
	krnl_ODBCDB,      //�ⲿ���ݿ�
	krnl_ODBCProvider,//�ⲿ�����ṩ��
	krnl_DropTarget,  //�ϷŶ���


	iext2_CartoonBox,
	iext2_IPEditBox,
	iext2_RichEdit,
	iext2_SplitterBar,
	iext2_SuperAnimateBox,
	iext2_SuperBtn,
};