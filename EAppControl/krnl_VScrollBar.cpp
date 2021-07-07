#include "krnl_VScrollBar.h"
#include "../common/public.h"

struct VScrollBar_UnitData
{
	unsigned int version;
	unsigned int ��Сλ��;
	unsigned int ���λ��;
	unsigned int ҳ�ı�ֵ;
	unsigned int �иı�ֵ;
	unsigned int λ��;
	unsigned int �����϶�����;
};

void krnl_VScrollBar::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("��Сλ��")] = 1;
	out_data[QStringLiteral("���λ��")] = 100;
	out_data[QStringLiteral("ҳ�ı�ֵ")] = 10;
	out_data[QStringLiteral("�иı�ֵ")] = 1;
	out_data[QStringLiteral("λ��")] = 1;
	out_data[QStringLiteral("�����϶�����")] = 1;
}

void krnl_VScrollBar::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	VScrollBar_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.��Сλ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���λ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ҳ�ı�ֵ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�иı�ֵ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.λ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�����϶����� = CDR_ReadUInt(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("��Сλ��")] = tmpData.��Сλ��;
	out_data[QStringLiteral("���λ��")] = tmpData.���λ��;
	out_data[QStringLiteral("ҳ�ı�ֵ")] = tmpData.ҳ�ı�ֵ;
	out_data[QStringLiteral("�иı�ֵ")] = tmpData.�иı�ֵ;
	out_data[QStringLiteral("λ��")] = tmpData.λ��;
	out_data[QStringLiteral("�����϶�����")] = tmpData.�����϶�����;
}

void krnl_VScrollBar::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����ı��ؼ�(QStringLiteral("��Сλ��"), map_ControlData[QStringLiteral("��Сλ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���λ��"), map_ControlData[QStringLiteral("���λ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("ҳ�ı�ֵ"), map_ControlData[QStringLiteral("ҳ�ı�ֵ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("�иı�ֵ"), map_ControlData[QStringLiteral("�иı�ֵ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("λ��"), map_ControlData[QStringLiteral("λ��")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�����϶�����"), map_ControlData[QStringLiteral("�����϶�����")].toBool());
}

qstring krnl_VScrollBar::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "λ�ñ��ı�";
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

QString krnl_VScrollBar::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/���������.ico");
}