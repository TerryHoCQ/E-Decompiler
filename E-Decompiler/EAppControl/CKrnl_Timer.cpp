#include "CKrnl_Timer.h"


CKrnl_Timer::CKrnl_Timer()
{
	type = krnl_Timer;
}

CKrnl_Timer* CKrnl_Timer::create()
{
	return new CKrnl_Timer();
}

std::string CKrnl_Timer::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�����¼�";
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}
	return ret;
}

bool CKrnl_Timer::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_Timer::GetPropertyName(unsigned int propertyIndex)
{
	switch (propertyIndex)
	{
	case 0:
		return "���";
	case 1:
		return "����";
	case 2:
		return "���";
	case 3:
		return "�߶�";
	case 4:
		return "���";
	case 5:
		return "����";
	case 6:
		return "��ֹ";
	case 7:
		return "���ָ��";
	case 8:
		return "ʱ������";
	}
	return "δ֪����";
}
