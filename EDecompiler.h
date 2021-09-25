#pragma once
#include <pro.h>
#include <QMap>
#include <QVariant>
#include "SectionManager.h"


enum EProgramsType_t
{
	E_UNKNOWN = 0,  //δ֪����
	E_DYNAMIC,      //��̬�������
	E_STATIC,       //��̬�������
};

#pragma pack(push,1)

struct EVENT_INFO
{
	uint32 m_lpszName;       //�¼�����
	uint32 m_lpszExplain;    //�¼���ϸ����
	uint32 m_dwState;        //�¼������־
	int32  m_nArgCount;      //�¼��Ĳ�����Ŀ
	uint32 m_lpEventArgInfo; //����
};

// �������崰�ڵ�Ԫ����
struct UNIT_PROPERTY
{
	uint32 m_lpszName;      //��������
	uint32 m_lpszEGName;    //Ӣ������
	uint32 m_lpszExplain;   //���Խ���
	int16  m_shtType;       //���Ե���������
	uint16 m_wState;        //���Ե�������
	uint32 m_lpszzPickStr;  //��ѡ�ı�
};

struct LIB_DATA_TYPE_INFO   //�ⶨ���������ͽṹ
{
	uint32 m_lpszName;     //����
	uint32 m_lpszEGName;   //Ӣ������,��Ϊ��
	uint32 m_szExplain;    //��ϸ����,��Ϊ��
	int32  m_nCmdCount;    //���������ͳ�Ա��������Ŀ(��Ϊ0)
	uint32 m_lpnCmdsIndex; //ָ�����г�Ա����������֧�ֿ�������е�����ֵָ��,��������ݱ�Ĩ��
	uint32 m_dwState;      //�������͵���������

	 ////////////////////////////////////////////
	// ���³�Աֻ����Ϊ���ڵ�Ԫ���˵�ʱ����Ч��

	uint32 m_dwUnitBmpID;     //ָ����֧�ֿ��еĵ�Ԫͼ����ԴID
	int32  m_nEventCount;     //����Ԫ���¼���Ŀ
	uint32 m_lpEventBegin;    //ָ��Ԫ�������¼���ָ��,EVENT_INFO,��������ݱ�Ĩ��
	int32 m_nPropertyCount;   //����Ԫ��������Ŀ
	uint32 m_lpPropertyBegin; //ָ��Ԫ���������Ե�ָ��,UNIT_PROPERTY

	uint32 m_lpfnGetInterface; //�����ṩ�����ڵ�Ԫ�����нӿڡ�

	////////////////////////////////////////////
	// ���³�Աֻ���ڲ�Ϊ���ڵ�Ԫ���˵�ʱ����Ч��

	int32 m_nElementCount;    //�������������ӳ�Ա����Ŀ(��Ϊ0)
	uint32 m_lpElementBegin;   //ָ���ӳ�Ա������׵�ַ,LIB_DATA_TYPE_ELEMENT
};

struct LIB_INFO
{
	uint32 m_dwLibFormatVer;    //֧�ֿ��ʽ�汾��,Ӧ��Ϊ0x1312D65
	uint32 m_lpGuid;            //��Ӧ֧�ֿ��GUIDָ�롣
	int32  m_nMajorVersion;     //֧�ֿ�����汾�ţ��������0��
	int32  m_nMinorVersion;     //֧�ֿ�Ĵΰ汾�š�
	int32  m_nBuildNumber;      //�����汾��
	int32  m_nRqSysMajorVer;    //����Ҫ������ϵͳ�����汾��
	int32  m_nRqSysMinorVer;    //����Ҫ������ϵͳ�Ĵΰ汾��
	int32  m_nRqSysKrnlLibMajorVer;   //����Ҫ��ϵͳ����֧�ֿ�����汾��
	int32  m_nRqSysKrnlLibMinorVer;   //����Ҫ��ϵͳ����֧�ֿ�Ĵΰ汾��
	uint32 m_lpName;            //֧�ֿ�����ָ��
	int32  m_nLanguage;         //֧�ֿ���֧�ֵ�����,Ӧ����1
	uint32 m_lpExplain;         //֧�ֿ��������ָ��,��Ϊ��
	uint32 m_dwState;           //֧�ֿ�����״̬˵��
	uint32 m_lpszAuthor;        //���������Ϣ
	uint32 m_lpszZipCode;       //���������Ϣ
	uint32 m_lpszAddress;       //���������Ϣ
	uint32 m_lpszPhone;         //���������Ϣ
	uint32 m_lpszFax;           //���������Ϣ
	uint32 m_lpszEmail;         //���������Ϣ
	uint32 m_lpszHomePage;      //���������Ϣ
	uint32 m_lpszOther;         //���������Ϣ

//////////////////
	int32 m_nDataTypeCount;     //֧�ֿ�ȫ�����������͸���
	uint32 m_lpDataType;        //ָ������õ�������������Ϣ��ָ��,LIB_DATA_TYPE_INFO

	int32 m_nCategoryCount;     //ȫ�����������Ŀ
	uint32 m_lpszzCategory;     //ȫ���������˵����ÿ��Ϊһ�ַ�����ǰ��λ���ֱ�ʾͼ�������ţ���1��ʼ��0��ʾ�ޣ���
		                        // ��һ���ֵΪָ��֧�ֿ�����Ϊ"LIB_BITMAP"��BITMAP��Դ��ĳһ����16X13λͼ������

	int32 m_nCmdCount;          //�������ṩ����������(ȫ��������󷽷�)����Ŀ(������Ϊ0)��
	uint32 m_lpBeginCmdInfo;    //ָ��������������Ķ�����Ϣ����(��m_nCmdCountΪ0,��ΪNULL),CMD_INFO
	uint32 m_lpCmdsFunc;        //ָ��ÿ�������ʵ�ִ����׵�ַ��(��m_nCmdCountΪ0, ��ΪNULL)��

	uint32 m_lpfnRunAddInFn;    //��ΪNULL������Ϊ������IDE�ṩ���ӹ���
	uint32 m_szzAddInFnInfo;    //�й�AddIn���ܵ�˵���������ַ���˵��һ������

	uint32 m_lpfnNotify;        //����ΪNULL���ṩ��������������IDE�����л���֪ͨ��Ϣ�ĺ�����

	// ����ģ����ʱ�������á�
	uint32 m_lpfnSuperTemplate;       //Ϊ��
	uint32 m_lpszzSuperTemplateInfo;  //Ϊ��

	// ���ⶨ������г�����
	int32 m_nLibConstCount;   //��������
	uint32 m_lpLibConst;      //ָ�������������ָ��

	uint32 m_lpszzDependFiles; //����������������Ҫ�����������ļ�����������װ���ʱ�����Զ�������Щ�ļ�,��Ϊ��
};

struct EHead
{
	uint32 dwMagic;  //δ֪,ֵ�̶�Ϊ3
	uint32 szNone2;  //δ֪,ֵ�̶�Ϊ0
	uint32 szNone3;  //δ֪,�����Ǹ������,�޸Ĳ�Ӱ�����
	uint32 lpStartCode;   //��ʼ�û������ַ,�����޸�
	uint32 lpEString;     //�ַ�����Դ,���û���ַ�����Դ,��Ϊ0
	uint32 dwEStringSize; //�ַ�����Դ��С,���û���ַ�����Դ,��Ϊ0
	uint32 lpEWindow;     //���������Ϣ
	uint32 dwEWindowSize; //���������Ϣ��С
	uint32 dwLibNum;      //֧�ֿ�����
	uint32 lpLibEntry;    //֧�ֿ���Ϣ���
	uint32 dwApiCount;    //Api����
	uint32 lpModuleName;  //ָ��ģ������
	uint32 lpApiName;     //ָ��Api����
};

#pragma pack(pop)



struct mid_EDataTypeInfo
{
	qstring m_Name;  //������������
};


struct mid_ELibInfo
{
	qstring m_Name;          //֧�ֿ�����
	qstring m_Guid;          //֧�ֿ��GUID
	int32  m_nMajorVersion;  //֧�ֿ�����汾�ţ��������0��
	int32  m_nMinorVersion;  //֧�ֿ�Ĵΰ汾�š�

	qvector<mid_EDataTypeInfo> mVec_DataTypeInfo;      //����������Ϣ
};

struct mid_KrnlJmp
{
	ea_t Jmp_MReportError;               //����ص�
	ea_t Jmp_MCallDllCmd;                //DLL����
	ea_t Jmp_MCallLibCmd;                //����֧�ֿ�����
	ea_t Jmp_MCallKrnlLibCmd;            //����֧�ֿ�����
	ea_t Jmp_MReadProperty;              //��ȡ�������
	ea_t Jmp_MWriteProperty;             //�����������
	ea_t Jmp_MMalloc;                    //�����ڴ�
	ea_t Jmp_MRealloc;                   //���·����ڴ�
	ea_t Jmp_MFree;                      //�ͷ��ڴ�
	ea_t Jmp_MExitProcess;               //����
	ea_t Jmp_MMessageLoop;               //������Ϣѭ��
	ea_t Jmp_MLoadBeginWin;              //������������
	ea_t Jmp_MOtherHelp;                 //��������
};

struct mid_KrnlApp
{
	ea_t krnl_MReportError;               //����ص�
	ea_t krnl_MCallDllCmd;                //DLL����
	ea_t krnl_MCallLibCmd;                //����֧�ֿ�����
	ea_t krnl_MCallKrnlLibCmd;            //����֧�ֿ�����
	ea_t krnl_MReadProperty;              //��ȡ�������
	ea_t krnl_MWriteProperty;             //�����������
	ea_t krnl_MMalloc;                    //�����ڴ�
	ea_t krnl_MRealloc;                   //���·����ڴ�
	ea_t krnl_MFree;                      //�ͷ��ڴ�
	ea_t krnl_MExitProcess;               //����
	ea_t krnl_MMessageLoop;               //������Ϣѭ��
	ea_t krnl_MLoadBeginWin;              //������������
	ea_t krnl_MOtherHelp;                 //��������
};

struct mid_EAppInfo
{
	ea_t m_UserCodeStartAddr;                          //�û���ʼ��ַ
	ea_t m_UserCodeEndAddr;                            //�û�������ַ,Ŀǰ��ʱ��û��ʲô�ð취��ȡ�����ַ,����кõ��뷨��ӭ��issue
	
	qvector<mid_ELibInfo>  mVec_LibInfo;               //֧�ֿ���Ϣ
	mid_KrnlApp m_KrnlApp;
	mid_KrnlJmp m_KrnlJmp;

	bool b_IsWindowProgram;                            //�Ƿ��Ǵ������

	unsigned int m_EventSum;                           //���еĿؼ��¼�����
};

class IDAMenu;
class EDecompilerEngine
{
public:
	EDecompilerEngine();
	~EDecompilerEngine();
public:
	//ɨ�������Ժ���
	void makeFunction(ea_t startAddr, ea_t endAddr);
	bool InitDecompilerEngine();
	bool DoDecompile();
	
	//���ݲ˵�������ID���õ�����
	static qstring GetControlTypeName(uint32 typeId);

	static ssize_t ui_callback(void* ud, int notification_code, va_list va);
private:
	//������̬���͵������Գ���
	bool Parse_EStatic();
	//̽�������Գ�������
	EProgramsType_t DetectProgramType();
	//����֧�ֿ���Ϣ
	bool ParseLibInfomation(ea_t, uint32);
	//����ϵͳ�ӿں���
	bool ParseKrnlInterface(ea_t);

	//ɨ�������Ի����⺯��
	void ScanEBasicLibFunc();
	bool SetKrnlJmpAddr(ea_t callAddr, ea_t setAddr);

public:
	EProgramsType_t m_ProgramType;
	mid_EAppInfo m_eAppInfo;
private:
	ea_t m_EHeadAddr;
	IDAMenu* gMenu_ShowResource = nullptr;
	IDAMenu* gMenu_ShowGUIInfo = nullptr;
	IDAMenu* gMenu_ShowEventInfo = nullptr;
	IDAMenu* gMenu_ShowImportsInfo = nullptr;
	
};

extern EDecompilerEngine g_MyDecompiler;