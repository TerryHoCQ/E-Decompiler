#include "EAppControl.h"

bool EAppControl::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string EAppControl::GetCommonEventName(int eventIndex)
{
	switch (eventIndex)
	{
	case -1:
		return "������������";
	case -2:
		return "���������ſ�";
	case -3:
		return "��˫��";
	case -4:
		return "����Ҽ�������";
	case -5:
		return "����Ҽ����ſ�";
	case -6:
		return "���λ�ñ��ƶ�";
	case -7:
		return "��ý���";
	case -8:
		return "ʧȥ����";
	case -9:
		return "����ĳ��";
	case -10:
		return "�ſ�ĳ��";
	case -11:
		return "�ַ�����";
	case -12:
		return "���ֱ�����";
	}
	return "δ֪�¼�";

}
