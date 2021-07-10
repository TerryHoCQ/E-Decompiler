#include "krnl_ChkListBox.h"
#include "../common/public.h"

struct ChkListBox_UnitData
{
	unsigned int version;
	unsigned int �߿�;
	unsigned int �Զ�����;
	unsigned int ����;
	unsigned int �м��;
	unsigned int ��ѡ;
	int ����ѡ����;
	qvector<unsigned char> ����;
	qvector<unsigned int> ��Ŀ��ֵ;
	qvector<qstring> �б���Ŀ;
};

QStringList krnl_ChkListBox::QStringListFromVec(qvector<qstring>& vec_str)
{
	QStringList ret;
	for (unsigned int n = 0; n < vec_str.size(); ++n) {
		ret.push_back(QString::fromLocal8Bit(vec_str[n].c_str()));
	}
	return ret;
}

QStringList krnl_ChkListBox::QStringListFromVec(qvector<unsigned int>& vec_str)
{
	QStringList ret;
	for (unsigned int n = 0; n < vec_str.size(); ++n) {
		ret.push_back(QString::number(vec_str[n]));
	}
	return ret;
}

QStringList krnl_ChkListBox::ȡ�߿��б�()
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

void krnl_ChkListBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("�߿�")] = 0x1;
	out_data[QStringLiteral("�Զ�����")] = 0x0;
	out_data[QStringLiteral("����")] = 0x0;
	out_data[QStringLiteral("�м��")] = 0x0;
	out_data[QStringLiteral("��ѡ")] = 0x0;
	out_data[QStringLiteral("����ѡ����")] = -1;
}

void krnl_ChkListBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	ChkListBox_UnitData tmpData;
	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�Զ����� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�м�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ѡ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����ѡ���� = CDR_ReadInt(pUnitDataPtr);

	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.��Ŀ��ֵ = CDR_ReadVecInt(pUnitDataPtr);

	tmpData.�б���Ŀ = CDR_ReadVecString(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("�Զ�����")] = tmpData.�Զ�����;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("�м��")] = tmpData.�м��;
	out_data[QStringLiteral("��ѡ")] = tmpData.��ѡ;
	out_data[QStringLiteral("����ѡ����")] = tmpData.����ѡ����;
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	out_data[QStringLiteral("��Ŀ��ֵ")] = QStringListFromVec(tmpData.��Ŀ��ֵ);
	out_data[QStringLiteral("�б���Ŀ")] = QStringListFromVec(tmpData.�б���Ŀ);
	return;
}

void krnl_ChkListBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�Զ�����"), map_ControlData[QStringLiteral("�Զ�����")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("�м��"), map_ControlData[QStringLiteral("�м��")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("��ѡ"), map_ControlData[QStringLiteral("��ѡ")].toBool());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
	EAppControl::����ı��ؼ�(QStringLiteral("����ѡ����"), map_ControlData[QStringLiteral("����ѡ����")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("�б���Ŀ"), map_ControlData[QStringLiteral("�б���Ŀ")].toStringList(), 0);
	EAppControl::����б�ؼ�(QStringLiteral("��Ŀ��ֵ"), map_ControlData[QStringLiteral("��Ŀ��ֵ")].toStringList(), 0);
}

qstring krnl_ChkListBox::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�б��ѡ��";
		break;
	case 1:
		ret = "ѡ��״̬���ı�";
		break;
	case 2:
		ret = "˫��ѡ��";
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

QString krnl_ChkListBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/ѡ���б��.ico");
}