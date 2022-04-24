#include "krnl_PicBox.h"
#include "../common/public.h"

struct PicBox_UnitData
{
	unsigned int version;
	unsigned int �߿�;
	unsigned int ������ɫ;
	unsigned int ��ʾ��ʽ;
	unsigned int ���Ŷ���;
	qvector<unsigned char> ͼƬ;
	qstring ����Դ;
	qstring ������;
};

QStringList krnl_PicBox::ȡ�߿��б�()
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

QStringList krnl_PicBox::ȡ��ʾ��ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("ͼƬ������"),
	QStringLiteral("����ͼƬ"),
	QStringLiteral("ͼƬ����"),
	};
	return Items;
}

void krnl_PicBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("�߿�")] = 0;
	out_data[QStringLiteral("������ɫ")] = 0xFF000000;
	out_data[QStringLiteral("��ʾ��ʽ")] = 0;
	out_data[QStringLiteral("���Ŷ���")] = 1;
}

void krnl_PicBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	PicBox_UnitData tmpData;
	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 2) {
		return;
	}
	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ʾ��ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���Ŷ��� = CDR_ReadUInt(pUnitDataPtr);

	tmpData.ͼƬ = CDR_ReadCFreqMem(pUnitDataPtr);
	if (tmpData.version == 2) {
		tmpData.����Դ = CDR_ReadCString(pUnitDataPtr);
		tmpData.������ = CDR_ReadCString(pUnitDataPtr);
	}

	//��������������������������������������������
	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	out_data[QStringLiteral("��ʾ��ʽ")] = tmpData.��ʾ��ʽ;
	out_data[QStringLiteral("���Ŷ���")] = tmpData.���Ŷ���;
	if (tmpData.ͼƬ.size()) {
		out_data[QStringLiteral("ͼƬ")] = QByteArray((char*)&tmpData.ͼƬ[0], tmpData.ͼƬ.size());
	}
	out_data[QStringLiteral("����Դ")] = QString::fromLocal8Bit(tmpData.����Դ.c_str());
	out_data[QStringLiteral("������")] = QString::fromLocal8Bit(tmpData.������.c_str());
	return;
}

void krnl_PicBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), krnl_PicBox::ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::���ͼƬ�ؼ�(QStringLiteral("ͼƬ"), map_ControlData[QStringLiteral("ͼƬ")].toByteArray());
	EAppControl::����б�ؼ�(QStringLiteral("    ��ʾ��ʽ"), krnl_PicBox::ȡ��ʾ��ʽ�б�(), map_ControlData[QStringLiteral("��ʾ��ʽ")].toUInt());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("���Ŷ���"), map_ControlData[QStringLiteral("���Ŷ���")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("����Դ"), map_ControlData[QStringLiteral("����Դ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("������"), map_ControlData[QStringLiteral("������")].toString());
	return;
}

QString krnl_PicBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/ͼƬ��.ico");
}

qstring krnl_PicBox::ȡ�¼�����(int eventIndex)
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