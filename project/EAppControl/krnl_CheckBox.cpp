#include "krnl_CheckBox.h"
#include "../common/public.h"

struct CheckBox_UnitData
{
	unsigned int version;
	unsigned int ��ť��ʽ;
	unsigned int ƽ��;
	unsigned int �������;
	unsigned int ������뷽ʽ;
	unsigned int ������뷽ʽ;
	unsigned int �ı���ɫ;
	unsigned int ������ɫ;
	unsigned int ѡ��;
	qvector<unsigned char> ͼƬ;
	qvector<unsigned char> ����;
	qstring ����;
	qstring ����Դ;
	qstring ������;
};

QStringList krnl_CheckBox::ȡ������뷽ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("���"),
	QStringLiteral("����"),
	QStringLiteral("�ұ�"),
	};
	return Items;
}

QStringList krnl_CheckBox::ȡ������뷽ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("����"),
	QStringLiteral("����"),
	QStringLiteral("�ױ�"),
	};
	return Items;
}

void krnl_CheckBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("��ť��ʽ")] = 0;
	out_data[QStringLiteral("ƽ��")] = 0;
	out_data[QStringLiteral("����")] = QStringLiteral("ѡ���");
	out_data[QStringLiteral("�������")] = 0;
	out_data[QStringLiteral("������뷽ʽ")] = 0;
	out_data[QStringLiteral("������뷽ʽ")] = 1;
	out_data[QStringLiteral("�ı���ɫ")] = 0;
	out_data[QStringLiteral("������ɫ")] = 0xFF000000;
	out_data[QStringLiteral("ѡ��")] = 0;
}

void krnl_CheckBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	CheckBox_UnitData tmpData;
	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 2) {
		return;
	}
	tmpData.��ť��ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ƽ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�ı���ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ѡ�� = CDR_ReadUInt(pUnitDataPtr);

	tmpData.ͼƬ = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	qstring ���� = CDR_ReadCString(pUnitDataPtr);
	if (tmpData.version == 2) {
		tmpData.����Դ = CDR_ReadCString(pUnitDataPtr);
		tmpData.������ = CDR_ReadCString(pUnitDataPtr);
	}

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("��ť��ʽ")] = tmpData.��ť��ʽ;
	out_data[QStringLiteral("ƽ��")] = tmpData.ƽ��;
	out_data[QStringLiteral("�������")] = tmpData.�������;
	out_data[QStringLiteral("������뷽ʽ")] = tmpData.������뷽ʽ;
	out_data[QStringLiteral("������뷽ʽ")] = tmpData.������뷽ʽ;
	out_data[QStringLiteral("�ı���ɫ")] = tmpData.�ı���ɫ;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	out_data[QStringLiteral("ѡ��")] = tmpData.ѡ��;
	if (tmpData.ͼƬ.size()) {
		out_data[QStringLiteral("ͼƬ")] = QByteArray((char*)&tmpData.ͼƬ[0], tmpData.ͼƬ.size());
	}
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	out_data[QStringLiteral("����")] = QString::fromLocal8Bit(tmpData.����.c_str());
	out_data[QStringLiteral("����Դ")] = QString::fromLocal8Bit(tmpData.����Դ.c_str());
	out_data[QStringLiteral("������")] = QString::fromLocal8Bit(tmpData.������.c_str());
}

void krnl_CheckBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::��Ӳ����ؼ�(QStringLiteral("��ͣ������"), map_ControlData[QStringLiteral("��ͣ������")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("    ͣ��˳��"), map_ControlData[QStringLiteral("ͣ��˳��")].toString());
	EAppControl::���ͼƬ�ؼ�(QStringLiteral("ͼƬ"), map_ControlData[QStringLiteral("ͼƬ")].toByteArray());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("��ť��ʽ"), map_ControlData[QStringLiteral("��ť��ʽ")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("ƽ��"), map_ControlData[QStringLiteral("ƽ��")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�������"), map_ControlData[QStringLiteral("�������")].toBool());
	EAppControl::����б�ؼ�(QStringLiteral("������뷽ʽ"), krnl_CheckBox::ȡ������뷽ʽ�б�(), map_ControlData[QStringLiteral("������뷽ʽ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("������뷽ʽ"), krnl_CheckBox::ȡ������뷽ʽ�б�(), map_ControlData[QStringLiteral("������뷽ʽ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�ı���ɫ"), map_ControlData[QStringLiteral("�ı���ɫ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("ѡ��"), map_ControlData[QStringLiteral("ѡ��")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("����Դ"), map_ControlData[QStringLiteral("����Դ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("������"), map_ControlData[QStringLiteral("������")].toString());
}


qstring krnl_CheckBox::ȡ�¼�����(int eventIndex)
{
	qstring ret;
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
	case -7:
		ret = "��ý���";
		break;
	case -8:
		ret = "ʧȥ����";
		break;
	case -9:
		ret = "����ĳ��";
		break;
	case -10:
		ret = "�ſ�ĳ��";
		break;
	case -11:
		ret = "�ַ�����";
		break;
	case -12:
		ret = "���ֱ�����";
	default:
		ret = "δ֪�¼�";
		break;
	}

	return ret;
}

QString krnl_CheckBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/ѡ���.ico");
}