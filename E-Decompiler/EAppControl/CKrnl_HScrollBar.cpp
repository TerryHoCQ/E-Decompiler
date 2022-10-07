#include "CKrnl_HScrollBar.h"


CKrnl_HScrollBar::CKrnl_HScrollBar()
{
	type = krnl_HScrollBar;
}

CKrnl_HScrollBar* CKrnl_HScrollBar::create()
{
	return new CKrnl_HScrollBar();
}

std::string CKrnl_HScrollBar::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "λ�ñ��ı�";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CKrnl_HScrollBar::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_HScrollBar::GetPropertyName(unsigned int propertyIndex)
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
		return "��Сλ��";
	case 9:
		return "���λ��";
	case 10:
		return "ҳ�ı�ֵ";
	case 11:
		return "�иı�ֵ";
	case 12:
		return "λ��";
	case 13:
		return "�����϶�����";
	}
	return "δ֪����";
}
