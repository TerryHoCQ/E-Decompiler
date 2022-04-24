#include "krnl_EditBox.h"
#include "../common/public.h"

struct EditBox_UnitData
{
	unsigned int version;
	unsigned int �߿�;
	unsigned int �ı���ɫ;
	unsigned int ������ɫ;
	unsigned int ����ѡ��;
	unsigned int ���������;
	unsigned int �Ƿ��������;
	unsigned int ������;
	unsigned int ���뷽ʽ;
	unsigned int ���뷽ʽ;
	char �����ڸ��ַ�;
	unsigned int ת����ʽ;
	unsigned int ��������ʽ;
	unsigned int ����������ֵ;
	unsigned int ����������ֵ;
	unsigned int ��ʼѡ��λ��;
	unsigned int ��ѡ���ַ���;
	qvector<unsigned char> ����;
	qstring ����;
	qstring ����Դ;
	qstring ������;
};

QStringList krnl_EditBox::ȡ�߿��б�()
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

QStringList krnl_EditBox::ȡ�������б�()
{
	QStringList Items = {
	QStringLiteral("��"),
	QStringLiteral("���������"),
	QStringLiteral("���������"),
	QStringLiteral("�������������"),
	};
	return Items;
}

QStringList krnl_EditBox::ȡ���뷽ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("�����"),
	QStringLiteral("����"),
	QStringLiteral("�Ҷ���"),
	};
	return Items;
}

QStringList krnl_EditBox::ȡ���뷽ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("ͨ����ʽ"),
	QStringLiteral("ֻ����ʽ"),
	QStringLiteral("��������"),
	QStringLiteral("�����ı�����"),
	QStringLiteral("С���ı�����"),
	QStringLiteral("�����ֽ�"),
	QStringLiteral("���������"),
	QStringLiteral("��������"),
	QStringLiteral("���볤����"),
	QStringLiteral("����С��"),
	QStringLiteral("����˫����С��"),
	QStringLiteral("��������ʱ�� "),
	};
	return Items;
}

QStringList krnl_EditBox::ȡת����ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("��"),
	QStringLiteral("��д->Сд"),
	QStringLiteral("Сд->��д"),
	};
	return Items;
}

QStringList krnl_EditBox::ȡ��������ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("�޵�����"),
	QStringLiteral("�Զ�������"),
	QStringLiteral("�ֶ�������"),
	};
	return Items;
}

void krnl_EditBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("�߿�")] = 1;
	out_data[QStringLiteral("�ı���ɫ")] = 0x0;
	out_data[QStringLiteral("������ɫ")] = 0xFFFFFF;
	out_data[QStringLiteral("����ѡ��")] = 0x1;
	out_data[QStringLiteral("���������")] = 0;
	out_data[QStringLiteral("�Ƿ��������")] = 0;
	out_data[QStringLiteral("������")] = 0x0;
	out_data[QStringLiteral("���뷽ʽ")] = 0x0;
	out_data[QStringLiteral("���뷽ʽ")] = 0x0;
	out_data[QStringLiteral("�����ڸ��ַ�")] = QString('*');
	out_data[QStringLiteral("ת����ʽ")] = 0x0;
	out_data[QStringLiteral("��������ʽ")] = 0x0;
	out_data[QStringLiteral("����������ֵ")] = 0x0;
	out_data[QStringLiteral("����������ֵ")] = 0x64;
	out_data[QStringLiteral("��ʼѡ��λ��")] = 0x0;
	out_data[QStringLiteral("��ѡ���ַ���")] = 0x0;
}

void krnl_EditBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	EditBox_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 2) {
		return;
	}

	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�ı���ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����ѡ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��������� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�Ƿ�������� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�����ڸ��ַ� = CDR_ReadChar(pUnitDataPtr);
	tmpData.ת����ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��������ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����������ֵ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����������ֵ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ʼѡ��λ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ѡ���ַ��� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.���� = CDR_ReadCString(pUnitDataPtr);
	if (tmpData.version == 2) {
		tmpData.����Դ = CDR_ReadCString(pUnitDataPtr);
		tmpData.������ = CDR_ReadCString(pUnitDataPtr);
	}
	
	//������������������������������������������������
	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("�ı���ɫ")] = tmpData.�ı���ɫ;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;

	out_data[QStringLiteral("����ѡ��")] = tmpData.����ѡ��;
	out_data[QStringLiteral("���������")] = tmpData.���������;
	out_data[QStringLiteral("�Ƿ��������")] = tmpData.�Ƿ��������;
	out_data[QStringLiteral("������")] = tmpData.������;
	out_data[QStringLiteral("���뷽ʽ")] = tmpData.���뷽ʽ;
	out_data[QStringLiteral("���뷽ʽ")] = tmpData.���뷽ʽ;
	out_data[QStringLiteral("�����ڸ��ַ�")] = QString(tmpData.�����ڸ��ַ�);
	out_data[QStringLiteral("ת����ʽ")] = tmpData.ת����ʽ;
	out_data[QStringLiteral("��������ʽ")] = tmpData.��������ʽ;
	out_data[QStringLiteral("����������ֵ")] = tmpData.����������ֵ;
	out_data[QStringLiteral("����������ֵ")] = tmpData.����������ֵ;
	out_data[QStringLiteral("��ʼѡ��λ��")] = tmpData.��ʼѡ��λ��;
	out_data[QStringLiteral("��ѡ���ַ���")] = tmpData.��ѡ���ַ���;
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	out_data[QStringLiteral("����")] = QString::fromLocal8Bit(tmpData.����.c_str());
	out_data[QStringLiteral("����Դ")] = QString::fromLocal8Bit(tmpData.����Դ.c_str());
	out_data[QStringLiteral("������")] = QString::fromLocal8Bit(tmpData.������.c_str());
	return;
}

void krnl_EditBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), krnl_EditBox::ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�ı���ɫ"), map_ControlData[QStringLiteral("�ı���ɫ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("����ѡ��"), map_ControlData[QStringLiteral("����ѡ��")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("���������"), map_ControlData[QStringLiteral("���������")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�Ƿ��������"), map_ControlData[QStringLiteral("�Ƿ��������")].toBool());
	EAppControl::����б�ؼ�(QStringLiteral("������"), krnl_EditBox::ȡ�������б�(), map_ControlData[QStringLiteral("������")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("���뷽ʽ"), krnl_EditBox::ȡ���뷽ʽ�б�(), map_ControlData[QStringLiteral("���뷽ʽ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("���뷽ʽ"), krnl_EditBox::ȡ���뷽ʽ�б�(), map_ControlData[QStringLiteral("���뷽ʽ")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("    �����ڸ��ַ�"), map_ControlData[QStringLiteral("�����ڸ��ַ�")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("ת����ʽ"), krnl_EditBox::ȡת����ʽ�б�(), map_ControlData[QStringLiteral("ת����ʽ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("��������ʽ"), krnl_EditBox::ȡ��������ʽ�б�(), map_ControlData[QStringLiteral("��������ʽ")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("    ����������ֵ"), map_ControlData[QStringLiteral("����������ֵ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("    ����������ֵ"), map_ControlData[QStringLiteral("����������ֵ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("��ʼѡ��λ��"), map_ControlData[QStringLiteral("��ʼѡ��λ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("��ѡ���ַ���"), map_ControlData[QStringLiteral("��ѡ���ַ���")].toString());
	EAppControl::�����Ч�ؼ�(QStringLiteral("��ѡ���ı�"), QStringLiteral("** ���ʱ������ **"));
	EAppControl::����ı��ؼ�(QStringLiteral("����Դ"), map_ControlData[QStringLiteral("����Դ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("������"), map_ControlData[QStringLiteral("������")].toString());
	return;
}

QString krnl_EditBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/�༭��.ico");
}

qstring krnl_EditBox::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "���ݱ��ı�";
		break;
	case 1:
		ret = "����ť������";
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
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}

	return ret;
}