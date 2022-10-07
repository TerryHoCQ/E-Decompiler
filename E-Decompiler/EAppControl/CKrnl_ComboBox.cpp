#include "CKrnl_ComboBox.h"

CKrnl_ComboBox::CKrnl_ComboBox()
{
	type = krnl_ComboBox;
}

CKrnl_ComboBox* CKrnl_ComboBox::create()
{
	return new CKrnl_ComboBox();
}

std::string CKrnl_ComboBox::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "�б��ѡ��";
	case 1:
		return "�༭���ݱ��ı�";
	case 2:
		return "�������б�";
	case 3:
		return "�б��ر�";
	case 4:
		return "˫��ѡ��";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CKrnl_ComboBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_ComboBox::GetPropertyName(unsigned int propertyIndex)
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
		return "����";
	case 10:
		return "����ı�����";
	case 11:
		return "��ʼѡ��λ��";
	case 12:
		return "��ѡ���ַ���";
	case 13:
		return "��ѡ���ı�";
	case 14:
		return "�Զ�����";
	case 15:
		return "�м��";
	case 16:
		return "�ı���ɫ";
	case 17:
		return "������ɫ";
	case 18:
		return "����";
	case 19:
		return "����ѡ����";
	case 20:
		return "�б���Ŀ";
	case 21:
		return "��Ŀ��ֵ";
	case 22:
		return "����Դ";
	case 23:
		return "������";
	case 24:
		return "��ȥ�ظ�";
	}
	return "δ֪����";
}
