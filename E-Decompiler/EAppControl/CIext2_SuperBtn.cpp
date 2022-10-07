#include "CIext2_SuperBtn.h"

CIext2_SuperBtn::CIext2_SuperBtn()
{
	type = iext2_SuperBtn;
}

CIext2_SuperBtn* CIext2_SuperBtn::create()
{
	return new CIext2_SuperBtn();
}

std::string CIext2_SuperBtn::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "������";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CIext2_SuperBtn::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CIext2_SuperBtn::GetPropertyName(unsigned int propertyIndex)
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
		return "��ť���";
	case 9:
		return "ѡ���ʽ";
	case 10:
		return "ѡ��";
	case 11:
		return "���뷽ʽ";
	case 12:
		return "ѹ�뷽ʽ";
	case 13:
		return "���Ʊ߿�";
	case 14:
		return "���ƽ���";
	case 15:
		return "ͨ��ͼƬ";
	case 16:
		return "ͨ��ͼƬ͸��ɫ";
	case 17:
		return "��ȼͼƬ";
	case 18:
		return "��ȼͼƬ͸��ɫ";
	case 19:
		return "��ֹͼƬ";
	case 20:
		return "��ֹͼƬ͸��ɫ";
	case 21:
		return "����";
	case 22:
		return "����";
	case 23:
		return "ʹ��Ĭ��ɫ";
	case 24:
		return "ͨ��ǰ��ɫ";
	case 25:
		return "ͨ������ɫ";
	case 26:
		return "��ȼǰ��ɫ";
	case 27:
		return "��ȼ����ɫ";
	case 28:
		return "����ǰ��ɫ";
	case 29:
		return "���㱳��ɫ";
	case 30:
		return "��׼����ʾ";
	case 31:
		return "������ʾ��";
	case 32:
		return "������ʾ��";
	case 33:
		return "��ʾ�ı�";
	case 34:
		return "Ĭ������";
	}
	return "δ֪�¼�";
}

