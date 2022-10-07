#include "CKrnl_SliderBar.h"


CKrnl_SliderBar::CKrnl_SliderBar()
{
	type = krnl_SliderBar;
}

CKrnl_SliderBar* CKrnl_SliderBar::create()
{
	return new CKrnl_SliderBar();
}

std::string CKrnl_SliderBar::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "�������";
	case 1:
		return "�ɷ񱻹ر�";
	case 2:
		return "��������";
	case 3:
		return "λ�ñ��ı�";
	case 4:
		return "�ߴ类�ı�";
	case 5:
		return "������";
	case 6:
		return "��ȡ������";
	case 7:
		return "����";
	case 8:
		return "�״μ���";
	case 9:
		return "�����¼�";
	case 10:
		return "����ʾ";
	case 11:
		return "������";
	case 12:
		return "���ڿɷ񱻹ر�";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CKrnl_SliderBar::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_SliderBar::GetPropertyName(unsigned int propertyIndex)
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
		return "����";
	case 10:
		return "�̶�����";
	case 11:
		return "��λ�̶�ֵ";
	case 12:
		return "����ѡ��";
	case 13:
		return "��ѡ��λ��";
	case 14:
		return "ѡ�񳤶�";
	case 15:
		return "ҳ�ı�ֵ";
	case 16:
		return "�иı�ֵ";
	case 17:
		return "��Сλ��";
	case 18:
		return "���λ��";
	case 19:
		return "λ��";
	}
	return "δ֪����";
}
