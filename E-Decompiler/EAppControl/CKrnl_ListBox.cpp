#include "CKrnl_ListBox.h"

CKrnl_ListBox::CKrnl_ListBox()
{
	type = krnl_ListBox;
}


CKrnl_ListBox* CKrnl_ListBox::create()
{
	return new CKrnl_ListBox();
}


std::string CKrnl_ListBox::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "�б��ѡ��";
	case 1:
		return "˫��ѡ��";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CKrnl_ListBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_ListBox::GetPropertyName(unsigned int propertyIndex)
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
		return "�ı���ɫ";
	case 13:
		return "������ɫ";
	case 14:
		return "����";
	case 15:
		return "����ѡ�����";
	case 16:
		return "����ѡ����";
	case 17:
		return "�б���Ŀ";
	case 18:
		return "��Ŀ��ֵ";
	case 19:
		return "����Դ";
	case 20:
		return "������";
	case 21:
		return "��ȥ�ظ�";
	}
	return "δ֪����";
}
