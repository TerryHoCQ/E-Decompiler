#include "krnl_Timer.h"
#include "../common/public.h"

struct Timer_UnitData
{
	unsigned int version;
	unsigned int ʱ������;
};

QString krnl_Timer::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/ʱ��.ico");
}

void krnl_Timer::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("ʱ������")] = 0;
}

void krnl_Timer::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	Timer_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}
	tmpData.ʱ������ = CDR_ReadUInt(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("ʱ������")] = tmpData.ʱ������;
	return;
}

void krnl_Timer::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
{
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���"), map_ControlData[QStringLiteral("���")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���"), map_ControlData[QStringLiteral("���")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("�߶�"), map_ControlData[QStringLiteral("�߶�")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���"), map_ControlData[QStringLiteral("���")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("ʱ������"), map_ControlData[QStringLiteral("ʱ������")].toString());
	return;
}

qstring krnl_Timer::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�����¼�";
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}
	return ret;
}