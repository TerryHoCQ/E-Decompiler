#pragma once
#include <map>

enum EKernelCallType
{
	UnknownError,           
	E_MReportError,         //����ص�
	E_MCallDllCmd,          //DLL����
	E_MCallLibCmd,          //����֧�ֿ�����
	E_MCallKrnlLibCmd,      //����֧�ֿ�����
	E_MReadProperty,        //��ȡ�������
	E_MWriteProperty,       //�����������
	E_MMalloc,              //�����ڴ�
	E_MRealloc,             //���·����ڴ�
	E_MFree,               //�ͷ��ڴ�
	E_MExitProcess,         //����
	E_MMessageLoop,         //������Ϣѭ��
	E_MLoadBeginWin,        //������������
	E_MOtherHelp            //��������
};

class EKernelLib
{
public:
	EKernelLib();
public:
	EKernelCallType GetKernelCallType(unsigned int callAddr);
public:
	//��ַ --> ����
	std::map<unsigned int, EKernelCallType> map_KernelCall;
};