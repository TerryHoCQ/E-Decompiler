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
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�б��ѡ��";
		break;
	case 1:
		ret = "�༭���ݱ��ı�";
		break;
	case 2:
		ret = "�������б�";
		break;
	case 3:
		ret = "�б��ر�";
		break;
	case 4:
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
