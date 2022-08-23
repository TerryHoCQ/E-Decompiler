#include "CKrnl_Tab.h"


CKrnl_Tab::CKrnl_Tab()
{
	type = krnl_Tab;
}

CKrnl_Tab* CKrnl_Tab::create()
{
	return new CKrnl_Tab();
}

std::string CKrnl_Tab::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "������";
		break;
	case 1:
		ret = "���ı��Ӽ�";
		break;
	case 2:
		ret = "�Ӽб��ı�";
		break;
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

bool CKrnl_Tab::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_Tab::GetPropertyName(unsigned int propertyIndex)
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
		return "��ͷ����";
	case 9:
		return "������б�ͷ";
	case 10:
		return "����";
	case 11:
		return "�Ӽй���";
	case 12:
		return "�����Ӽ�";
	case 13:
		return "��������";
	case 14:
		return "�Ƿ���䱳��";
	case 15:
		return "������ɫ";
	}
	return "δ֪����";
}
