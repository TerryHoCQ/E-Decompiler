#include "CKrnl_ProcessBar.h"

CKrnl_ProcessBar::CKrnl_ProcessBar()
{
	type = krnl_ProcessBar;
}

CKrnl_ProcessBar* CKrnl_ProcessBar::create()
{
	return new CKrnl_ProcessBar();
}

std::string CKrnl_ProcessBar::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case -1:
		ret = "������������";
		break;
	case -2:
		ret = "���������ſ�";
		break;
	case -3:
		ret = "��˫��";
		break;
	case -4:
		ret = "����Ҽ�������";
		break;
	case -5:
		ret = "����Ҽ����ſ�";
		break;
	case -6:
		ret = "���λ�ñ��ƶ�";
		break;
	case -12:
		ret = "���ֱ�����";
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}

	return ret;
}

bool CKrnl_ProcessBar::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_ProcessBar::GetPropertyName(unsigned int propertyIndex)
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
		return "�߿�";
	case 9:
		return "����";
	case 10:
		return "��ʾ��ʽ";
	case 11:
		return "��Сλ��";
	case 12:
		return "���λ��";
	case 13:
		return "λ��";
	}
	return "δ֪����";
}
