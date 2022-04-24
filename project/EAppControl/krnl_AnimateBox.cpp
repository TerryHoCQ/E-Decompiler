#include "krnl_AnimateBox.h"
#include "EAppControl.h"
#include "../common/public.h"

struct AnimateBox_UnitData
{
	unsigned int version;
	unsigned int ���в���;
	unsigned int ͸������;
	unsigned int ����;
	int ���Ŵ���;
	qstring �ļ���;
};


QString krnl_AnimateBox::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/Ӱ���.ico");
}

void krnl_AnimateBox::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	AnimateBox_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.���в��� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.͸������ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���Ŵ��� = CDR_ReadInt(pUnitDataPtr);
	tmpData.�ļ��� = CDR_ReadCString(pUnitDataPtr);

	//����������������������������������������������������
	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("���в���")] = tmpData.���в���;
	out_data[QStringLiteral("͸������")] = tmpData.͸������;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("���Ŵ���")] = tmpData.���Ŵ���;
	out_data[QStringLiteral("�ļ���")] = QString::fromLocal8Bit(tmpData.�ļ���.c_str());
}

void krnl_AnimateBox::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("���в���")] = 1;
	out_data[QStringLiteral("͸������")] = 1;
	out_data[QStringLiteral("����")] = 1;
	out_data[QStringLiteral("���Ŵ���")] = -1;
}

qstring krnl_AnimateBox::ȡ�¼�����(int eventIndex)
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

void krnl_AnimateBox::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����ı��ؼ�(QStringLiteral("�ļ���"), map_ControlData[QStringLiteral("�ļ���")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("���в���"), map_ControlData[QStringLiteral("���в���")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("͸������"), map_ControlData[QStringLiteral("͸������")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("���Ŵ���"), map_ControlData[QStringLiteral("���Ŵ���")].toBool());
}