#include "krnl_DropTarget.h"

qstring krnl_DropTarget::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�õ��ı�";
		break;
	case 1:
		ret = "�õ����ı�";
		break;
	case 2:
		ret = "�õ�URL";
		break;
	case 3:
		ret = "�õ��ļ�";
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}

	return ret;
}