#include "CKrnl_ShapeBox.h"

CKrnl_ShapeBox::CKrnl_ShapeBox()
{
	type = krnl_ShapeBox;
}

CKrnl_ShapeBox* CKrnl_ShapeBox::create()
{
	return new CKrnl_ShapeBox();
}

std::string CKrnl_ShapeBox::GetEventName(int eventIndex)
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

bool CKrnl_ShapeBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_ShapeBox::GetPropertyName(unsigned int propertyIndex)
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
		return "������ɫ";
	case 9:
		return "����";
	case 10:
		return "����Ч��";
	case 11:
		return "����";
	case 12:
		return "�߿�";
	case 13:
		return "������ɫ";
	case 14:
		return "�����ɫ";
	}
	return "δ֪����";
}
