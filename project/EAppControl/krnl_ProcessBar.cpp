#include "krnl_ProcessBar.h"
#include "../common/public.h"

struct ProcessBar_UnitData
{
	unsigned int version;
	unsigned int �߿�;
	unsigned int ����;
	unsigned int ��ʾ��ʽ;
	unsigned int ��Сλ��;
	unsigned int ���λ��;
	unsigned int λ��;
};

QStringList krnl_ProcessBar::ȡ�߿��б�()
{
	QStringList Items = {
		QStringLiteral("�ޱ߿�"),
		QStringLiteral("����ʽ"),
		QStringLiteral("͹��ʽ"),
		QStringLiteral("ǳ����ʽ"),
		QStringLiteral("����ʽ"),
		QStringLiteral("���߱߿�ʽ"),
	};
	return Items;
}

QStringList krnl_ProcessBar::ȡ�����б�()
{
	QStringList Items = {
		QStringLiteral("����"),
		QStringLiteral("����"),
	};
	return Items;
}

QStringList krnl_ProcessBar::ȡ��ʾ��ʽ�б�()
{
	QStringList Items = {
		QStringLiteral("�ֿ�"),
		QStringLiteral("����"),
	};
	return Items;

}

void krnl_ProcessBar::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("�߿�")] = 1;
	out_data[QStringLiteral("���λ��")] = 100;
	out_data[QStringLiteral("ҳ�ı�ֵ")] = 10;
	out_data[QStringLiteral("�иı�ֵ")] = 1;
	out_data[QStringLiteral("λ��")] = 1;
	out_data[QStringLiteral("�����϶�����")] = 1;
}

void krnl_ProcessBar::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	ProcessBar_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ʾ��ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��Сλ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���λ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.λ�� = CDR_ReadUInt(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("��ʾ��ʽ")] = tmpData.��ʾ��ʽ;
	out_data[QStringLiteral("��Сλ��")] = tmpData.��Сλ��;
	out_data[QStringLiteral("���λ��")] = tmpData.���λ��;
	out_data[QStringLiteral("λ��")] = tmpData.λ��;
}

void krnl_ProcessBar::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
{
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���"), map_ControlData[QStringLiteral("���")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���"), map_ControlData[QStringLiteral("���")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("�߶�"), map_ControlData[QStringLiteral("�߶�")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���"), map_ControlData[QStringLiteral("���")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("��ֹ"), map_ControlData[QStringLiteral("��ֹ")].toBool());
	EAppControl::������ؼ�(map_ControlData[QStringLiteral("���ָ��")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), krnl_ProcessBar::ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("����"), krnl_ProcessBar::ȡ�����б�(), map_ControlData[QStringLiteral("����")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("��ʾ��ʽ"), krnl_ProcessBar::ȡ��ʾ��ʽ�б�(), map_ControlData[QStringLiteral("��ʾ��ʽ")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("��Сλ��"), map_ControlData[QStringLiteral("��Сλ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���λ��"), map_ControlData[QStringLiteral("���λ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("λ��"), map_ControlData[QStringLiteral("λ��")].toString());
}

qstring krnl_ProcessBar::ȡ�¼�����(int eventIndex)
{
	qstring ret;
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
	case -12:
		ret = "���ֱ�����";
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}

	return ret;
}

QString krnl_ProcessBar::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/������.ico");
}