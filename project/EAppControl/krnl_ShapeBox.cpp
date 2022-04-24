#include "krnl_ShapeBox.h"
#include "../common/public.h"

struct ShapeBox_UnitData
{
	unsigned int version;
	unsigned int ������ɫ;
	unsigned int ����;
	unsigned int ����Ч��;
	unsigned int ����;
	unsigned int �߿�;
	unsigned int ������ɫ;
	unsigned int �����ɫ;
};

QStringList krnl_ShapeBox::ȡ�����б�()
{
	QStringList Items = {
		QStringLiteral("����"),
		QStringLiteral("������"),
		QStringLiteral("��Բ"),
		QStringLiteral("Բ"),
		QStringLiteral("Բ�Ǿ���"),
		QStringLiteral("Բ��������"),
		QStringLiteral("������"),
		QStringLiteral("������"),
	};
	return Items;
}

QStringList krnl_ShapeBox::ȡ����Ч���б�()
{
	QStringList Items = {
	QStringLiteral("ͨ��"),
	QStringLiteral("����"),
	QStringLiteral("͹��"),
	};
	return Items;
}

QStringList krnl_ShapeBox::ȡ�����б�()
{
	QStringList Items = {
	QStringLiteral("��"),
	QStringLiteral("ֱ��"),
	QStringLiteral("����"),
	QStringLiteral("����"),
	QStringLiteral("�㻮��"),
	QStringLiteral("˫�㻮��"),
	};
	return Items;
}

void krnl_ShapeBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("������ɫ")] = 0xFF000000;
	out_data[QStringLiteral("����")] = 0x0;
	out_data[QStringLiteral("����Ч��")] = 0x0;
	out_data[QStringLiteral("����")] = 0x1;
	out_data[QStringLiteral("�߿�")] = 0x1;
	out_data[QStringLiteral("������ɫ")] = 0x0;
	out_data[QStringLiteral("�����ɫ")] = 0xFF000000;
}

void krnl_ShapeBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	ShapeBox_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����Ч�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�����ɫ = CDR_ReadUInt(pUnitDataPtr);

	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("����Ч��")] = tmpData.����Ч��;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	out_data[QStringLiteral("�����ɫ")] = tmpData.�����ɫ;
	return;
}

void krnl_ShapeBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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

	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("����"), krnl_ShapeBox::ȡ�����б�(), map_ControlData[QStringLiteral("����")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("����Ч��"), krnl_ShapeBox::ȡ����Ч���б�(), map_ControlData[QStringLiteral("����Ч��")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("����"), krnl_ShapeBox::ȡ�����б�(), map_ControlData[QStringLiteral("����")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("�߿�"), map_ControlData[QStringLiteral("�߿�")].toString());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�����ɫ"), map_ControlData[QStringLiteral("�����ɫ")].toUInt());
}

QString krnl_ShapeBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/���ο�.ico");
}

qstring krnl_ShapeBox::ȡ�¼�����(int eventIndex)
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