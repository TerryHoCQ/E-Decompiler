#include "CKrnl_PicBtn.h"

CKrnl_PicBtn::CKrnl_PicBtn()
{
	type = krnl_PicBtn;
}

CKrnl_PicBtn* CKrnl_PicBtn::create()
{
	return new CKrnl_PicBtn();
}

std::string CKrnl_PicBtn::GetEventName(int eventIndex)
{
	std::string ret;
	switch (eventIndex)
	{
	case 0:
		ret = "������";
		break;
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
	case -12:
		ret = "���ֱ�����";
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}
	return ret;
}

bool CKrnl_PicBtn::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_PicBtn::GetPropertyName(unsigned int propertyIndex)
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
		return "ѡ��";
	case 10:
		return "����ͼƬ";
	case 11:
		return "��ȼͼƬ";
	case 12:
		return "����ͼƬ";
	case 13:
		return "��ֹͼƬ";
	case 14:
		return "͸����ɫ";
	}
	return "δ֪����";
}
