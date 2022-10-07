#include "CKrnl_GroupBox.h"

CKrnl_GroupBox::CKrnl_GroupBox()
{
	type = krnl_GroupBox;
}

CKrnl_GroupBox* CKrnl_GroupBox::create()
{
	return new CKrnl_GroupBox();
}

std::string CKrnl_GroupBox::GetEventName(int eventIndex)
{
	return GetCommonEventName(eventIndex);
}

bool CKrnl_GroupBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_GroupBox::GetPropertyName(unsigned int propertyIndex)
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
		return "���뷽ʽ";
	case 10:
		return "�ı���ɫ";
	case 11:
		return "������ɫ";
	case 12:
		return "����";
	}
	return "δ֪����";
}
