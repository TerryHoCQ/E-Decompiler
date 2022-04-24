#include "krnl_ComboBox.h"
#include "../common/public.h"

struct ComboBox_UnitData
{
	unsigned int version;
	unsigned int ����;
	unsigned int ����ı�����;
	unsigned int ��ʼѡ��λ��;
	unsigned int ��ѡ���ַ���;
	unsigned int �Զ�����;
	unsigned int �м��;
	unsigned int �ı���ɫ;
	unsigned int ������ɫ;
	int ����ѡ����;
	qvector<unsigned char> ����;
	qvector<unsigned int> ��Ŀ��ֵ;
	qstring ����;
	qvector<qstring> �б���Ŀ;
	qstring ����Դ;
	qstring ������;
	unsigned int Unknow;
};

QStringList krnl_ComboBox::QStringListFromVec(qvector<qstring>& vec_str)
{
	QStringList ret;
	for (unsigned int n = 0; n < vec_str.size(); ++n) {
		ret.push_back(QString::fromLocal8Bit(vec_str[n].c_str()));
	}
	return ret;
}

QStringList krnl_ComboBox::QStringListFromVec(qvector<unsigned int>& vec_str)
{
	QStringList ret;
	for (unsigned int n = 0; n < vec_str.size(); ++n) {
		ret.push_back(QString::number(vec_str[n]));
	}
	return ret;
}

QStringList krnl_ComboBox::ȡ�����б�()
{
	QStringList Items = {
	QStringLiteral("�ɱ༭�б�ʽ"),
	QStringLiteral("�ɱ༭����ʽ"),
	QStringLiteral("���ɱ༭����ʽ"),
	};
	return Items;
}

void krnl_ComboBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("����")] = 0x1;
	out_data[QStringLiteral("����ı�����")] = 0x0;
	out_data[QStringLiteral("��ʼѡ��λ��")] = 0x0;
	out_data[QStringLiteral("��ѡ���ַ���")] = 0x0;
	out_data[QStringLiteral("�Զ�����")] = 0x0;
	out_data[QStringLiteral("�м��")] = 0x1;
	out_data[QStringLiteral("�ı���ɫ")] = 0x0;
	out_data[QStringLiteral("������ɫ")] = 0xFFFFFF;
	out_data[QStringLiteral("����ѡ����")] = -1;
}

void krnl_ComboBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	ComboBox_UnitData tmpData;
	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 3) {
		return;
	}
	
	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����ı����� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ʼѡ��λ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ѡ���ַ��� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�Զ����� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�м�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�ı���ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����ѡ���� = CDR_ReadInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);

	tmpData.��Ŀ��ֵ = CDR_ReadVecInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadCString(pUnitDataPtr);
	tmpData.�б���Ŀ = CDR_ReadVecString(pUnitDataPtr);

	if (tmpData.version >= 2) {
		tmpData.����Դ = CDR_ReadCString(pUnitDataPtr);
		tmpData.������ = CDR_ReadCString(pUnitDataPtr);
	}

	if (tmpData.version >= 3) {
		tmpData.Unknow = CDR_ReadUInt(pUnitDataPtr);
	}

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("����ı�����")] = tmpData.����ı�����;
	out_data[QStringLiteral("��ʼѡ��λ��")] = tmpData.��ʼѡ��λ��;
	out_data[QStringLiteral("��ѡ���ַ���")] = tmpData.��ѡ���ַ���;
	out_data[QStringLiteral("�Զ�����")] = tmpData.�Զ�����;
	out_data[QStringLiteral("�м��")] = tmpData.�м��;
	out_data[QStringLiteral("�ı���ɫ")] = tmpData.�ı���ɫ;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	out_data[QStringLiteral("����ѡ����")] = tmpData.����ѡ����;
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	out_data[QStringLiteral("��Ŀ��ֵ")] = QStringListFromVec(tmpData.��Ŀ��ֵ);
	out_data[QStringLiteral("����")] = QString::fromLocal8Bit(tmpData.����.c_str());
	out_data[QStringLiteral("�б���Ŀ")] = QStringListFromVec(tmpData.�б���Ŀ);
	out_data[QStringLiteral("����Դ")] = QString::fromLocal8Bit(tmpData.����Դ.c_str());
	out_data[QStringLiteral("������")] = QString::fromLocal8Bit(tmpData.������.c_str());

	return;
}

void krnl_ComboBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����б�ؼ�(QStringLiteral("����"), krnl_ComboBox::ȡ�����б�(), map_ControlData[QStringLiteral("����")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("����ı�����"), map_ControlData[QStringLiteral("����ı�����")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("��ʼѡ��λ��"), map_ControlData[QStringLiteral("��ʼѡ��λ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("��ѡ���ַ���"), map_ControlData[QStringLiteral("��ѡ���ַ���")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�Զ�����"), map_ControlData[QStringLiteral("�Զ�����")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("�м��"), map_ControlData[QStringLiteral("�м��")].toString());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�ı���ɫ"), map_ControlData[QStringLiteral("�ı���ɫ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
	EAppControl::����ı��ؼ�(QStringLiteral("����ѡ����"), map_ControlData[QStringLiteral("����ѡ����")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("�б���Ŀ"), map_ControlData[QStringLiteral("�б���Ŀ")].toStringList(), 0);
	EAppControl::����б�ؼ�(QStringLiteral("��Ŀ��ֵ"), map_ControlData[QStringLiteral("��Ŀ��ֵ")].toStringList(), 0);
	EAppControl::����ı��ؼ�(QStringLiteral("����Դ"), map_ControlData[QStringLiteral("����Դ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("������"), map_ControlData[QStringLiteral("������")].toString());
}

qstring krnl_ComboBox::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�б��ѡ��";
		break;
	case 1:
		ret = "�༭���ݱ��ı�";
		break;
	case 2:
		ret = "�������б�";
		break;
	case 3:
		ret = "�б��ر�";
		break;
	case 4:
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

QString krnl_ComboBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/��Ͽ�.ico");
}
