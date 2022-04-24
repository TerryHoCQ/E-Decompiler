#include "krnl_GroupBox.h"
#include "../common/public.h"

struct GroupBox_UnitData
{
	unsigned int version;
	unsigned int ���뷽ʽ;
	unsigned int �ı���ɫ;
	unsigned int ������ɫ;
	qvector<unsigned char> ����;
	qstring ����;
};

QStringList krnl_GroupBox::ȡ���뷽ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("���"),
	QStringLiteral("����"),
	QStringLiteral("�ұ�"),
	};
	return Items;
}

void krnl_GroupBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("���뷽ʽ")] = 0x0;
	out_data[QStringLiteral("�ı���ɫ")] = 0x0;
	out_data[QStringLiteral("������ɫ")] = 0xFF000000;
}

void krnl_GroupBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	GroupBox_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.���뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�ı���ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.���� = CDR_ReadCString(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("���뷽ʽ")] = tmpData.���뷽ʽ;
	out_data[QStringLiteral("�ı���ɫ")] = tmpData.�ı���ɫ;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	out_data[QStringLiteral("����")] = QString::fromLocal8Bit(tmpData.����.c_str());
}

void krnl_GroupBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("���뷽ʽ"), krnl_GroupBox::ȡ���뷽ʽ�б�(), map_ControlData[QStringLiteral("���뷽ʽ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�ı���ɫ"), map_ControlData[QStringLiteral("�ı���ɫ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
}

qstring krnl_GroupBox::ȡ�¼�����(int eventIndex)
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

QString krnl_GroupBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/�����.ico");
}