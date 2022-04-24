#include "krnl_Tab.h"
#include "../common/public.h"

struct Tab_UnitData
{
	unsigned int version;
	unsigned int ��ͷ����;
	unsigned int ������б�ͷ;
	unsigned int �����Ӽ�;
	unsigned int ��������;
	unsigned int �Ƿ���䱳��;
	unsigned int ������ɫ;
	qvector<unsigned char> ����;
	qvector<qstring> �Ӽй���;
};

QStringList krnl_Tab::QStringListFromVec(qvector<qstring>& vec_str)
{
	QStringList ret;
	for (unsigned int n = 0; n < vec_str.size(); ++n) {
		ret.push_back(QString::fromLocal8Bit(vec_str[n].c_str()));
	}
	return ret;
}

QStringList krnl_Tab::ȡ��ͷ�����б�()
{
	QStringList Items = {
		QStringLiteral("��"),
		QStringLiteral("��"),
		QStringLiteral("��"),
		QStringLiteral("��"),
	};
	return Items;
}

QString krnl_Tab::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/ѡ���.ico");
}

void krnl_Tab::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("��ͷ����")] = 0x0;
	out_data[QStringLiteral("������б�ͷ")] = 0x0;
	out_data[QStringLiteral("��������")] = 0x0;
	out_data[QStringLiteral("�Ƿ���䱳��")] = 0x1;
	out_data[QStringLiteral("������ɫ")] = 0xFF000000;
}

void krnl_Tab::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	Tab_UnitData tmpData = {};

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 3) {
		return;
	}
	
	tmpData.��ͷ���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������б�ͷ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�����Ӽ� = CDR_ReadUInt(pUnitDataPtr);

	if (tmpData.version >= 2) {
		tmpData.�������� = CDR_ReadUInt(pUnitDataPtr);
	}

	if (tmpData.version < 3) {
		tmpData.�Ƿ���䱳�� = 0x0;
	}
	else {
		tmpData.�Ƿ���䱳�� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	}
	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.�Ӽй��� = CDR_ReadVecString(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("��ͷ����")] = tmpData.��ͷ����;
	out_data[QStringLiteral("������б�ͷ")] = tmpData.������б�ͷ;
	out_data[QStringLiteral("�����Ӽ�")] = tmpData.�����Ӽ�;
	out_data[QStringLiteral("��������")] = tmpData.��������;
	out_data[QStringLiteral("��������")] = tmpData.��������;
	out_data[QStringLiteral("�Ƿ���䱳��")] = tmpData.�Ƿ���䱳��;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;

	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	out_data[QStringLiteral("�Ӽй���")] = QStringListFromVec(tmpData.�Ӽй���);
	return;
}

void krnl_Tab::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����б�ؼ�(QStringLiteral("��ͷ����"), krnl_Tab::ȡ��ͷ�����б�(), map_ControlData[QStringLiteral("��ͷ����")].toUInt());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("������б�ͷ"), map_ControlData[QStringLiteral("������б�ͷ")].toBool());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
	EAppControl::����б�ؼ�(QStringLiteral("�Ӽй���"), map_ControlData[QStringLiteral("�Ӽй���")].toStringList(), 0);
	EAppControl::����ı��ؼ�(QStringLiteral("�����Ӽ�"), QStringLiteral("** ���ʱ������ **"));
	EAppControl::��Ӳ����ؼ�(QStringLiteral("��������"), map_ControlData[QStringLiteral("��������")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("    �Ƿ���䱳��"), map_ControlData[QStringLiteral("�Ƿ���䱳��")].toBool());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("    ������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	return;
}

qstring krnl_Tab::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "������";
		break;
	case 1:
		ret = "���ı��Ӽ�";
		break;
	case 2:
		ret = "�Ӽб��ı�";
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