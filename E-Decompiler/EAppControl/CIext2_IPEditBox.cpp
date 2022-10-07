#include "CIext2_IPEditBox.h"

CIext2_IPEditBox::CIext2_IPEditBox()
{
	type = iext2_IPEditBox;
}

CIext2_IPEditBox* CIext2_IPEditBox::create()
{
	return new CIext2_IPEditBox();
}

std::string CIext2_IPEditBox::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "��ַ���ı�";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CIext2_IPEditBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CIext2_IPEditBox::GetPropertyName(unsigned int propertyIndex)
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
		return "��ַ";
	}
	return "δ֪����";
}

