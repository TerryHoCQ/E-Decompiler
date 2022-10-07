#include "CIext2_SplitterBar.h"

CIext2_SplitterBar::CIext2_SplitterBar()
{
	type = iext2_SplitterBar;
}

CIext2_SplitterBar* CIext2_SplitterBar::create()
{
	return new CIext2_SplitterBar();
}

std::string CIext2_SplitterBar::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "���϶�";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CIext2_SplitterBar::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CIext2_SplitterBar::GetPropertyName(unsigned int propertyIndex)
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
	}
	return "δ֪����";
}

