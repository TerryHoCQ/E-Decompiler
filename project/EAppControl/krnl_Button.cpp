#include "krnl_Button.h"
#include "EAppControl.h"
#include "../common/public.h"

struct Button_UnitData
{
	unsigned int version;
	unsigned int ����;
	unsigned int ������뷽ʽ;
	unsigned int ������뷽ʽ;
	qvector<unsigned char> ͼƬ;
	qvector<unsigned char> ����;
	qstring ����;
};

QStringList krnl_Button::ȡ�����б�()
{
	QStringList Items = {
		QStringLiteral("ͨ��"),
		QStringLiteral("Ĭ��"),
	};
	return Items;
}

QStringList krnl_Button::ȡ������뷽ʽ�б�()
{
	QStringList Items = {
		QStringLiteral("���"),
		QStringLiteral("����"),
		QStringLiteral("�ұ�"),
	};
	return Items;
}

QStringList krnl_Button::ȡ������뷽ʽ�б�()
{
	QStringList Items = {
		QStringLiteral("����"),
		QStringLiteral("����"),
		QStringLiteral("�ױ�"),
	};
	return Items;
}

QString krnl_Button::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/��ť.ico");
}

void krnl_Button::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	Button_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ͼƬ = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.���� = CDR_ReadCString(pUnitDataPtr);

	//����������������������������������������������������
	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("������뷽ʽ")] = tmpData.������뷽ʽ;
	out_data[QStringLiteral("������뷽ʽ")] = tmpData.������뷽ʽ;
	if (tmpData.ͼƬ.size()) {
		out_data[QStringLiteral("ͼƬ")] = QByteArray((char*)&tmpData.ͼƬ[0], tmpData.ͼƬ.size());
	}
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	out_data[QStringLiteral("����")] = QString::fromLocal8Bit(tmpData.����.c_str());
}

void krnl_Button::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("����")] = 0;
	out_data[QStringLiteral("������뷽ʽ")] = 1;
	out_data[QStringLiteral("������뷽ʽ")] = 1;
	out_data[QStringLiteral("����")] = QStringLiteral("��ť");
}

qstring krnl_Button::ȡ�¼�����(int eventIndex)
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
		break;
	default:
		ret = "δ֪�¼�";
		break;
	}
	return ret;
}

void krnl_Button::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����б�ؼ�(QStringLiteral("����"), krnl_Button::ȡ�����б�(), map_ControlData[QStringLiteral("����")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("������뷽ʽ"), krnl_Button::ȡ������뷽ʽ�б�(), map_ControlData[QStringLiteral("������뷽ʽ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("������뷽ʽ"), krnl_Button::ȡ������뷽ʽ�б�(), map_ControlData[QStringLiteral("������뷽ʽ")].toUInt());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
}