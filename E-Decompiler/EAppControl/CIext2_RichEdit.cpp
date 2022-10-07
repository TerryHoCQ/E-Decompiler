#include "CIext2_RichEdit.h"

CIext2_RichEdit::CIext2_RichEdit()
{
	type = iext2_RichEdit;
}

CIext2_RichEdit* CIext2_RichEdit::create()
{
	return new CIext2_RichEdit();
}

std::string CIext2_RichEdit::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "���ݱ��ı�";
	case 1:
		return "ѡ�������ı�";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CIext2_RichEdit::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CIext2_RichEdit::GetPropertyName(unsigned int propertyIndex)
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
		return "���ݸ�ʽ";
	case 9:
		return "����";
	case 10:
		return "�߿�";
	case 11:
		return "������ɫ";
	case 12:
		return "�Ƿ��������";
	case 13:
		return "�Զ�����";
	case 14:
		return "ֻ��";
	case 15:
		return "����ѡ��";
	case 16:
		return "���������";
	case 17:
		return "��ʼѡ��λ��";
	case 18:
		return "��ѡ���ַ���";
	case 19:
		return "��ѡ���ı�";
	case 20:
		return "�Ƿ��Ѹ���";
	}
	return "δ֪����";
}

