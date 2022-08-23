#include "CKrnl_Button.h"

CKrnl_Button::CKrnl_Button()
{
	type = eSymbol_ControlType::krnl_Button;
}

CKrnl_Button* CKrnl_Button::create()
{
	return new CKrnl_Button();
}

std::string CKrnl_Button::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "������";
	case -1:
		return "������������";
	case -2:
		return "���������ſ�";
	case -3:
		return "��˫��";
		break;
	case -4:
		return "����Ҽ�������";
		break;
	case -5:
		return "����Ҽ����ſ�";
		break;
	case -6:
		return "���λ�ñ��ƶ�";
		break;
	case -7:
		return "��ý���";
		break;
	case -8:
		return "ʧȥ����";
		break;
	case -9:
		return "����ĳ��";
		break;
	case -10:
		return "�ſ�ĳ��";
		break;
	case -11:
		return "�ַ�����";
		break;
	case -12:
		return "���ֱ�����";
		break;
	}
	return "δ֪�¼�";
}

bool CKrnl_Button::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_Button::GetPropertyName(unsigned int propertyIndex)
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
		return "����";
	case 10:
		return "����";
	case 11:
		return "������뷽ʽ";
	case 12:
		return "������뷽ʽ";
	case 13:
		return "����";
	}
	return "δ֪����";
}
