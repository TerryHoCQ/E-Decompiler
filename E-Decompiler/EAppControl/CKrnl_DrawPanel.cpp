#include "CKrnl_DrawPanel.h"

CKrnl_DrawPanel::CKrnl_DrawPanel()
{
	type = krnl_DrawPanel;
}

CKrnl_DrawPanel* CKrnl_DrawPanel::create()
{
	return new CKrnl_DrawPanel();
}

std::string CKrnl_DrawPanel::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "�滭";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CKrnl_DrawPanel::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_DrawPanel::GetPropertyName(unsigned int propertyIndex)
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
		return "�߿�";
	case 9:
		return "���屳��ɫ";
	case 10:
		return "��ͼ";
	case 11:
		return "��ͼ��ʽ";
	case 12:
		return "�Զ��ػ�";
	case 13:
		return "�滭��λ";
	case 14:
		return "��������";
	case 15:
		return "������ʽ";
	case 16:
		return "���ʴ�ϸ";
	case 17:
		return "������ɫ";
	case 18:
		return "ˢ������";
	case 19:
		return "ˢ����ɫ";
	case 20:
		return "�ı���ɫ";
	case 21:
		return "�ı�������ɫ";
	case 22:
		return "����";
	case 23:
		return "������";
	case 24:
		return "����߶�";
	}
	return "δ֪����";
}
