#pragma once

#pragma pack(push,1)

// �������崰�ڵ�Ԫ����
struct UNIT_PROPERTY
{
	unsigned int m_lpszName;      //��������
	unsigned int m_lpszEGName;    //Ӣ������
	unsigned int m_lpszExplain;   //���Խ���
	short  m_shtType;             //���Ե���������
	unsigned short m_wState;      //���Ե�������
	unsigned int m_lpszzPickStr;  //��ѡ�ı�
};

//�ⶨ���������ͽṹ
struct LIB_DATA_TYPE_INFO   
{
	unsigned int m_lpszName;     //����
	unsigned int m_lpszEGName;   //Ӣ������,��Ϊ��
	unsigned int m_szExplain;    //��ϸ����,��Ϊ��
	int  m_nCmdCount;    //���������ͳ�Ա��������Ŀ(��Ϊ0)
	unsigned int m_lpnCmdsIndex; //ָ�����г�Ա����������֧�ֿ�������е�����ֵָ��,��������ݱ�Ĩ��
	unsigned int m_dwState;      //�������͵���������

	 ////////////////////////////////////////////
	// ���³�Աֻ����Ϊ���ڵ�Ԫ���˵�ʱ����Ч��

	unsigned int m_dwUnitBmpID;     //ָ����֧�ֿ��еĵ�Ԫͼ����ԴID
	int  m_nEventCount;     //����Ԫ���¼���Ŀ
	unsigned int m_lpEventBegin;    //ָ��Ԫ�������¼���ָ��,EVENT_INFO,��������ݱ�Ĩ��
	int m_nPropertyCount;   //����Ԫ��������Ŀ
	unsigned int m_lpPropertyBegin; //ָ��Ԫ���������Ե�ָ��,UNIT_PROPERTY

	unsigned int m_lpfnGetInterface; //�����ṩ�����ڵ�Ԫ�����нӿڡ�

	////////////////////////////////////////////
	// ���³�Աֻ���ڲ�Ϊ���ڵ�Ԫ���˵�ʱ����Ч��

	int m_nElementCount;    //�������������ӳ�Ա����Ŀ(��Ϊ0)
	unsigned int m_lpElementBegin;   //ָ���ӳ�Ա������׵�ַ,LIB_DATA_TYPE_ELEMENT
};

struct LIB_INFO
{
	unsigned int m_dwLibFormatVer;    //֧�ֿ��ʽ�汾��,Ӧ��Ϊ0x1312D65
	unsigned int m_lpGuid;            //��Ӧ֧�ֿ��GUIDָ�롣
	int  m_nMajorVersion;     //֧�ֿ�����汾�ţ��������0��
	int  m_nMinorVersion;     //֧�ֿ�Ĵΰ汾�š�
	int  m_nBuildNumber;      //�����汾��
	int  m_nRqSysMajorVer;    //����Ҫ������ϵͳ�����汾��
	int  m_nRqSysMinorVer;    //����Ҫ������ϵͳ�Ĵΰ汾��
	int  m_nRqSysKrnlLibMajorVer;   //����Ҫ��ϵͳ����֧�ֿ�����汾��
	int  m_nRqSysKrnlLibMinorVer;   //����Ҫ��ϵͳ����֧�ֿ�Ĵΰ汾��
	unsigned int m_lpName;            //֧�ֿ�����ָ��
	int  m_nLanguage;         //֧�ֿ���֧�ֵ�����,Ӧ����1
	unsigned int m_lpExplain;         //֧�ֿ��������ָ��,��Ϊ��
	unsigned int m_dwState;           //֧�ֿ�����״̬˵��
	unsigned int m_lpszAuthor;        //���������Ϣ
	unsigned int m_lpszZipCode;       //���������Ϣ
	unsigned int m_lpszAddress;       //���������Ϣ
	unsigned int m_lpszPhone;         //���������Ϣ
	unsigned int m_lpszFax;           //���������Ϣ
	unsigned int m_lpszEmail;         //���������Ϣ
	unsigned int m_lpszHomePage;      //���������Ϣ
	unsigned int m_lpszOther;         //���������Ϣ

//////////////////
	int m_nDataTypeCount;     //֧�ֿ�ȫ�����������͸���
	unsigned int m_lpDataType;        //ָ������õ�������������Ϣ��ָ��,LIB_DATA_TYPE_INFO

	int m_nCategoryCount;     //ȫ�����������Ŀ
	unsigned int m_lpszzCategory;     //ȫ���������˵����ÿ��Ϊһ�ַ�����ǰ��λ���ֱ�ʾͼ�������ţ���1��ʼ��0��ʾ�ޣ���
								// ��һ���ֵΪָ��֧�ֿ�����Ϊ"LIB_BITMAP"��BITMAP��Դ��ĳһ����16X13λͼ������

	int m_nCmdCount;          //�������ṩ����������(ȫ��������󷽷�)����Ŀ(������Ϊ0)��
	unsigned int m_lpBeginCmdInfo;    //ָ��������������Ķ�����Ϣ����(��m_nCmdCountΪ0,��ΪNULL),CMD_INFO
	unsigned int m_lpCmdsFunc;        //ָ��ÿ�������ʵ�ִ����׵�ַ��(��m_nCmdCountΪ0, ��ΪNULL)��

	unsigned int m_lpfnRunAddInFn;    //��ΪNULL������Ϊ������IDE�ṩ���ӹ���
	unsigned int m_szzAddInFnInfo;    //�й�AddIn���ܵ�˵���������ַ���˵��һ������

	unsigned int m_lpfnNotify;        //����ΪNULL���ṩ��������������IDE�����л���֪ͨ��Ϣ�ĺ�����

	// ����ģ����ʱ�������á�
	unsigned int m_lpfnSuperTemplate;       //Ϊ��
	unsigned int m_lpszzSuperTemplateInfo;  //Ϊ��

	// ���ⶨ������г�����
	int m_nLibConstCount;   //��������
	unsigned int m_lpLibConst;      //ָ�������������ָ��

	unsigned int m_lpszzDependFiles; //����������������Ҫ�����������ļ�����������װ���ʱ�����Զ�������Щ�ļ�,��Ϊ��
};

#pragma pack(pop)

enum ControlType_t
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
};

struct EStaticHead
{
	unsigned int dwMagic;  //δ֪,ֵ�̶�Ϊ3
	unsigned int szNone2;  //δ֪,ֵ�̶�Ϊ0
	unsigned int szNone3;  //δ֪,�����Ǹ������,�޸Ĳ�Ӱ�����
	unsigned int lpStartCode;   //��ʼ�û������ַ,�����޸�
	unsigned int lpEString;     //�ַ�����Դ,���û���ַ�����Դ,��Ϊ0
	unsigned int dwEStringSize; //�ַ�����Դ��С,���û���ַ�����Դ,��Ϊ0
	unsigned int lpEWindow;     //���������Ϣ
	unsigned int dwEWindowSize; //���������Ϣ��С
	unsigned int dwLibNum;      //֧�ֿ�����
	unsigned int lpLibEntry;    //֧�ֿ���Ϣ���
	unsigned int dwApiCount;    //Api����
	unsigned int lpModuleName;  //ָ��ģ������
	unsigned int lpApiName;     //ָ��Api����
};
