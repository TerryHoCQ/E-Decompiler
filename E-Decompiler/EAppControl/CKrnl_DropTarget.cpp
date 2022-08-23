#include "CKrnl_DropTarget.h"


CKrnl_DropTarget::CKrnl_DropTarget()
{
	type = krnl_DropTarget;
}

CKrnl_DropTarget* CKrnl_DropTarget::create()
{
	return new CKrnl_DropTarget();
}

std::string CKrnl_DropTarget::GetEventName(int eventIndex)
{
	std::string ret;
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

bool CKrnl_DropTarget::InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize)
{
	return true;
}

std::string CKrnl_DropTarget::GetPropertyName(unsigned int propertyIndex)
{
	return "δ֪����";
}
