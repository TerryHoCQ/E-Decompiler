#include "CKrnl_RadioBox.h"

CKrnl_RadioBox::CKrnl_RadioBox()
{
	type = krnl_RadioBox;
}

CKrnl_RadioBox* CKrnl_RadioBox::create()
{
	return new CKrnl_RadioBox();
}

std::string CKrnl_RadioBox::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "������";
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
	case -7:
		ret = "��ý���";
		break;
	case -8:
		ret = "ʧȥ����";
		break;
	case -9:
		ret = "����ĳ��";
		break;
	case -10:
		ret = "�ſ�ĳ��";
		break;
	case -11:
		ret = "�ַ�����";
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

bool CKrnl_RadioBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_RadioBox::GetPropertyName(unsigned int propertyIndex)
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
		return "ͼƬ";
	case 9:
		return "��ť��ʽ";
	case 10:
		return "ƽ��";
	case 11:
		return "����";
	case 12:
		return "�������";
	case 13:
		return "������뷽ʽ";
	case 14:
		return "������뷽ʽ";
	case 15:
		return "�ı���ɫ";
	case 16:
		return "������ɫ";
	case 17:
		return "����";
	case 18:
		return "ѡ��";
	}
	return "δ֪����";
}
