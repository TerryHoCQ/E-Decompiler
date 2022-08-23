#include "CKrnl_Label.h"


CKrnl_Label::CKrnl_Label()
{
	type = krnl_Label;
}

CKrnl_Label* CKrnl_Label::create()
{
	return new CKrnl_Label();
}

std::string CKrnl_Label::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�����¼�";
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

bool CKrnl_Label::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_Label::GetPropertyName(unsigned int propertyIndex)
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
		return "����";
	case 9:
		return "Ч��";
	case 10:
		return "�߿�";
	case 11:
		return "����߿���";
	case 12:
		return "����߿���ɫ1";
	case 13:
		return "����߿���ɫ2";
	case 14:
		return "����߿���ɫ3";
	case 15:
		return "����";
	case 16:
		return "�ı���ɫ";
	case 17:
		return "������ɫ";
	case 18:
		return "��ͼ";
	case 19:
		return "��ͼ��ʽ";
	case 20:
		return "���䱳����ʽ";
	case 21:
		return "���䱳����ɫ1";
	case 22:
		return "���䱳����ɫ2";
	case 23:
		return "���䱳����ɫ3";
	case 24:
		return "������뷽ʽ";
	case 25:
		return "�Ƿ��Զ�����";
	case 26:
		return "������뷽ʽ";
	case 27:
		return "����Դ";
	case 28:
		return "������";
	}
	return "δ֪����";
}
