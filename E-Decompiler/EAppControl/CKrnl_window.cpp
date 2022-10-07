#include "CKrnl_window.h"


CKrnl_window::CKrnl_window()
{
	type = krnl_window;
}

CKrnl_window* CKrnl_window::create()
{
	return new CKrnl_window();
}

std::string CKrnl_window::GetEventName(int eventIndex)
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

bool CKrnl_window::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{


	return true;
}

std::string CKrnl_window::GetPropertyName(unsigned int propertyIndex)
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
		return "�߿�";
	case 10:
		return "��ɫ";
	case 11:
		return "��ͼ";
	case 12:
		return "��ͼ��ʽ";
	case 13:
		return "��������";
	case 14:
		return "���Ŵ���";
	case 15:
		return "���ư�ť";
	case 16:
		return "��󻯰�ť";
	case 17:
		return "��С����ť";
	case 18:
		return "λ��";
	case 19:
		return "�ɷ��ƶ�";
	case 20:
		return "ͼ��";
	case 21:
		return "�س����ƽ���";
	case 22:
		return "Esc���ر�";
	case 23:
		return "F1���򿪰���";
	case 24:
		return "�����ļ���";
	case 25:
		return "������־ֵ";
	case 26:
		return "������������ʾ";
	case 27:
		return "�����ƶ�";
	case 28:
		return "����";
	case 29:
		return "������ǰ";
	case 30:
		return "���ֱ���������";
	case 31:
		return "��������";
	}
	return "δ֪����";
}
