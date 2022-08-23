#pragma once
#include <string>
#include <vector>
#include "../ELib.h"

struct EAppControl
{
public:
	//ȡ�¼�������Ӧ������
	virtual std::string GetEventName(int eventIndex) = 0;
	//���ؿؼ�������������
	virtual bool InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize);
	//��ȡ��������
	virtual std::string GetPropertyName(unsigned int propertyIndex) = 0;
public:
	eSymbol_ControlType type;
	//�ؼ���������ID
	unsigned int windowID;
	//�ؼ�����ID
	unsigned int controlId;
	//�ؼ�����
	std::string controlName;
	//�ؼ������������͵�ID
	unsigned int controlTypeId;
	//�ؼ���������
	std::string controlTypeName;
	//���Ե�ַ
	unsigned int propertyAddr;
	//���Դ�С
	int propertySize;
	//�¼�����
	std::vector<eSymbol_EventInfo> eventList;
};

struct EAppControl_Unknow :public EAppControl
{
public:
	static EAppControl_Unknow* create();
public:
	std::string GetEventName(int eventIndex) override;
	bool InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize) override;
	std::string GetPropertyName(unsigned int propertyIndex) override;
};