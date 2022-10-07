#include "CKrnl_AnimateBox.h"

CKrnl_AnimateBox::CKrnl_AnimateBox()
{
	type = krnl_AnimateBox;
}

CKrnl_AnimateBox* CKrnl_AnimateBox::create()
{
	return new CKrnl_AnimateBox();
}

std::string CKrnl_AnimateBox::GetEventName(int eventIndex)
{
	return GetCommonEventName(eventIndex);
}

bool CKrnl_AnimateBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_AnimateBox::GetPropertyName(unsigned int propertyIndex)
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
		return "�ļ���";
	case 9:
		return "���в���";
	case 10:
		return "͸������";
	case 11:
		return "����";
	case 12:
		return "���Ŵ���";
	}
	return "δ֪����";
}
