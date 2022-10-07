#include "CIext2_CartoonBox.h"

CIext2_CartoonBox::CIext2_CartoonBox()
{
	type = iext2_CartoonBox;
}

CIext2_CartoonBox* CIext2_CartoonBox::create()
{
	return new CIext2_CartoonBox();
}

std::string CIext2_CartoonBox::GetEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case 0:
		return "�������������";
	case 1:
		return "�����Ҽ�������";
	case 2:
		return "����������ſ�";
	case 3:
		return "�����Ҽ����ſ�";
	case 4:
		return "˫������";
	case 5:
		return "��������";
	case 6:
		return "�뿪����";
	case 7:
		return "���������λ�øı�";
	case 8:
		return "����λ�ý��ı�";
	case 9:
		return "����λ���Ѹı�";
	case 10:
		return "���彫����";
	case 11:
		return "��ײ������";
	case 12:
		return "��ײ���߽�";
	case 13:
		return "Խ���߽�";
	case 14:
		return "�Զ�ǰ��ֹͣ";
	case 15:
		return "�Զ���תֹͣ";
	case 16:
		return "�����������";
	case 17:
		return "���Ӽ�������";
	default:
		break;
	}
	return GetCommonEventName(eventIndex);
}

bool CIext2_CartoonBox::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CIext2_CartoonBox::GetPropertyName(unsigned int propertyIndex)
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
		return "������ɫ";
	case 10:
		return "����ͼƬ";
	case 11:
		return "��ʾ��ʽ";
	case 12:
		return "��������";
	case 13:
		return "������ʽ";
	case 14:
		return "���ʴ�ϸ";
	case 15:
		return "������ɫ";
	case 16:
		return "ˢ������";
	case 17:
		return "ˢ����ɫ";
	case 18:
		return "�ı���ɫ";
	case 19:
		return "�ı�������ɫ";
	case 20:
		return "����";
	}
	return "δ֪����";
}

