#pragma once
#include "EKernelLib.h"
#include "EObject_Include.h"
#include "IDAArchitecture.h"
#include <vector>
#include <string>

//�����Ծ�̬����ܹ�

struct mid_ELibInfo
{
	std::string m_Name;     //֧�ֿ�����
	std::string m_Guid;     //֧�ֿ��GUID
	int  m_nMajorVersion;   //֧�ֿ�����汾�ţ��������0��
	int  m_nMinorVersion;   //֧�ֿ�Ĵΰ汾�š�
};

struct mid_EAppInfo
{
	unsigned int m_UserCodeStartAddr;                //�û���ʼ��ַ
	unsigned int m_UserCodeEndAddr;                  //�û�������ַ,Ŀǰ��ʱ��û��ʲô�ð취��ȡ�����ַ,����кõ��뷨��ӭ��issue

	std::vector<mid_ELibInfo>  mVec_LibInfo;         //֧�ֿ���Ϣ
	//mid_KrnlApp m_KrnlApp;
	//mid_KrnlJmp m_KrnlJmp;
	bool b_IsWindowProgram;                          //�Ƿ��Ǵ������
};

class EStaticArchitecture:public IDAArchitecture
{
public:
	EStaticArchitecture();
	~EStaticArchitecture();
	//������̬���͵������Գ���
	bool Parse_EStatic(unsigned int eHeadAddr);

	//ִ�з����붯��
	void performActions() override;
private:
	//����֧�ֿ���Ϣ
	bool ParseLibInfomation(unsigned int lpLibStartAddr, unsigned int dwLibCount);

	//����ϵͳ�ӿں���
	bool ParseKrnlInterface(unsigned int);

	//void buildAction(DocumentStorage& store) override;
public:
	//���ĺ���
	EKernelLib m_KernelLib;

	//�������е�������Ϣ
	mid_EAppInfo m_eAppInfo;
	//�ؼ�ID -> �ؼ�����
	std::map<unsigned int, ControlType_t> m_ControlMapping;

	std::map<unsigned int, std::string> map_KernelFunc;
};