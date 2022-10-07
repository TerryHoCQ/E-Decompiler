#include "CIext2_SuperAnimateBox.h"

CIext2_SuperAnimateBox::CIext2_SuperAnimateBox()
{
	type = iext2_SuperAnimateBox;
}

CIext2_SuperAnimateBox* CIext2_SuperAnimateBox::create()
{
	return new CIext2_SuperAnimateBox();
}

std::string CIext2_SuperAnimateBox::GetEventName(int eventIndex)
{
	return GetCommonEventName(eventIndex);
}

bool CIext2_SuperAnimateBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CIext2_SuperAnimateBox::GetPropertyName(unsigned int propertyIndex)
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
		return "����λ��";
	case 9:
		return "Ӱ���ļ���";
	case 10:
		return "�����ٶ�";
	case 11:
		return "������ɫ";
	case 12:
		return "͸����ɫ";
	case 13:
		return "����";
	case 14:
		return "������һ��";
	case 15:
		return "��ǰ֡";
	case 16:
		return "ȫ��֡��";
	}
	return "δ֪����";
}

