#include "CKrnl_EditBox.h"

CKrnl_EditBox::CKrnl_EditBox()
{
	type = krnl_EditBox;
}

CKrnl_EditBox* CKrnl_EditBox::create()
{
	return new CKrnl_EditBox();
}

std::string CKrnl_EditBox::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "���ݱ��ı�";
		break;
	case 1:
		ret = "����ť������";
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

bool CKrnl_EditBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_EditBox::GetPropertyName(unsigned int propertyIndex)
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
		return "�߿�";
	case 10:
		return "�ı���ɫ";
	case 11:
		return "������ɫ";
	case 12:
		return "����";
	case 13:
		return "����ѡ��";
	case 14:
		return "���������";
	case 15:
		return "�Ƿ��������";
	case 16:
		return "������";
	case 17:
		return "���뷽ʽ";
	case 18:
		return "���뷽ʽ";
	case 19:
		return "�����ڸ��ַ�";
	case 20:
		return "ת����ʽ";
	case 21:
		return "��������ʽ";
	case 22:
		return "����������ֵ";
	case 23:
		return "����������ֵ";
	case 24:
		return "��ʼѡ��λ��";
	case 25:
		return "��ѡ���ַ���";
	case 26:
		return "��ѡ���ı�";
	case 27:
		return "����Դ";
	case 28:
		return "������";
	}
	return "δ֪����";
}
