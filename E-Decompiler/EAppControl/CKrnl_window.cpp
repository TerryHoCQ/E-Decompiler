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
	std::string ret;
	switch (eventIndex)
	{
	case -1:
		ret = "������������";
		break;
	case -2:
		ret = "���������ſ�";
		break;
	case -3:
		ret = "��˫��";
		break;
	case -4:
		ret = "����Ҽ�������";
		break;
	case -5:
		ret = "����Ҽ����ſ�";
		break;
	case -6:
		ret = "���λ�ñ��ƶ�";
		break;
	case -7:
		ret = "��ý���";
		break;
	case -8:
		ret = "ʧȥ����";
		break;
	case -9:
		ret = "����ĳ��";
		break;
	case -10:
		ret = "�ſ�ĳ��";
		break;
	case -11:
		ret = "�ַ�����";
		break;
	case -12:
		ret = "���ֱ�����";
		break;
	case 0:
		ret = "�������";
		break;
	case 1:
		ret = "�ɷ񱻹ر�";
		break;
	case 2:
		ret = "��������";
		break;
	case 3:
		ret = "λ�ñ��ı�";
		break;
	case 4:
		ret = "�ߴ类�ı�";
		break;
	case 5:
		ret = "������";
		break;
	case 6:
		ret = "��ȡ������";
		break;
	case 7:
		ret = "����";
		break;
	case 8:
		ret = "�״μ���";
		break;
	case 9:
		ret = "�����¼�";
		break;
	case 10:
		ret = "����ʾ";
		break;
	case 11:
		ret = "������";
		break;
	case 12:
		ret = "���ڿɷ񱻹ر�";
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}
	return ret;
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
