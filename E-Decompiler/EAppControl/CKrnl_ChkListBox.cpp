#include "CKrnl_ChkListBox.h"


CKrnl_ChkListBox::CKrnl_ChkListBox()
{
	type = krnl_ChkListBox;
}

CKrnl_ChkListBox* CKrnl_ChkListBox::create()
{
	return new CKrnl_ChkListBox();
}

std::string CKrnl_ChkListBox::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�б��ѡ��";
		break;
	case 1:
		ret = "ѡ��״̬���ı�";
		break;
	case 2:
		ret = "˫��ѡ��";
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
	default:
		ret = "δ֪�¼�";
		break;
	}

	return ret;
}

bool CKrnl_ChkListBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_ChkListBox::GetPropertyName(unsigned int propertyIndex)
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
		return "�Զ�����";
	case 10:
		return "����";
	case 11:
		return "�м��";
	case 12:
		return "��ѡ";
	case 13:
		return "����";
	case 14:
		return "����ѡ����";
	case 15:
		return "�б���Ŀ";
	case 16:
		return "��Ŀ��ֵ";
	}
	return "δ֪����";
}
