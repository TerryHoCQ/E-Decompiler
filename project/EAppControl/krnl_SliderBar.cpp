#include "krnl_SliderBar.h"
#include "../common/public.h"

struct SliderBar_UnitData
{
	unsigned int version;
	unsigned int �߿�;
	unsigned int ����;
	unsigned int �̶�����;
	unsigned int ��λ�̶�ֵ;
	unsigned int ����ѡ��;
	unsigned int ��ѡ��λ��;
	unsigned int ѡ�񳤶�;
	unsigned int ҳ�ı�ֵ;
	unsigned int �иı�ֵ;
	unsigned int ��Сλ��;
	unsigned int ���λ��;
	unsigned int λ��;
};

QStringList krnl_SliderBar::ȡ�߿��б�()
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

QStringList krnl_SliderBar::ȡ�����б�()
{
	QStringList Items = {
		QStringLiteral("����"),
		QStringLiteral("����"),
	};
	return Items;
}

QStringList krnl_SliderBar::ȡ�̶������б�()
{
	QStringList Items = {
		QStringLiteral("��"),
		QStringLiteral("��/��"),
		QStringLiteral("��/��"),
		QStringLiteral("˫��"),
	};
	return Items;
}

void krnl_SliderBar::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("�߿�")] = 0x0;
	out_data[QStringLiteral("����")] = 0x0;
	out_data[QStringLiteral("�̶�����")] = 0x2;
	out_data[QStringLiteral("��λ�̶�ֵ")] = 0x1;
	out_data[QStringLiteral("����ѡ��")] = 0x0;
	out_data[QStringLiteral("��ѡ��λ��")] = 0x0;
	out_data[QStringLiteral("ѡ�񳤶�")] = 0x0;
	out_data[QStringLiteral("ҳ�ı�ֵ")] = 0x5;
	out_data[QStringLiteral("�иı�ֵ")] = 0x1;
	out_data[QStringLiteral("��Сλ��")] = 1;
	out_data[QStringLiteral("���λ��")] = 10;
	out_data[QStringLiteral("λ��")] = 0x1;
}

void krnl_SliderBar::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	SliderBar_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�̶����� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��λ�̶�ֵ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����ѡ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ѡ��λ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ѡ�񳤶� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ҳ�ı�ֵ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�иı�ֵ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��Сλ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���λ�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.λ�� = CDR_ReadUInt(pUnitDataPtr);
	
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("�̶�����")] = tmpData.�̶�����;
	out_data[QStringLiteral("��λ�̶�ֵ")] = tmpData.��λ�̶�ֵ;
	out_data[QStringLiteral("����ѡ��")] = tmpData.����ѡ��;
	out_data[QStringLiteral("��ѡ��λ��")] = tmpData.��ѡ��λ��;
	out_data[QStringLiteral("ѡ�񳤶�")] = tmpData.ѡ�񳤶�;
	out_data[QStringLiteral("ҳ�ı�ֵ")] = tmpData.ҳ�ı�ֵ;
	out_data[QStringLiteral("�иı�ֵ")] = tmpData.�иı�ֵ;
	out_data[QStringLiteral("��Сλ��")] = tmpData.��Сλ��;
	out_data[QStringLiteral("���λ��")] = tmpData.���λ��;
	out_data[QStringLiteral("λ��")] = tmpData.λ��;
	return;
}

void krnl_SliderBar::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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

	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), krnl_SliderBar::ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("����"), krnl_SliderBar::ȡ�����б�(), map_ControlData[QStringLiteral("����")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("�̶�����"), krnl_SliderBar::ȡ�̶������б�(), map_ControlData[QStringLiteral("�̶�����")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("    ��λ�̶�ֵ"), map_ControlData[QStringLiteral("��λ�̶�ֵ")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("����ѡ��"), map_ControlData[QStringLiteral("����ѡ��")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("    ��ѡ��λ��"), map_ControlData[QStringLiteral("��ѡ��λ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("    ѡ�񳤶�"), map_ControlData[QStringLiteral("ѡ�񳤶�")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("ҳ�ı�ֵ"), map_ControlData[QStringLiteral("ҳ�ı�ֵ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("�иı�ֵ"), map_ControlData[QStringLiteral("�иı�ֵ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("��Сλ��"), map_ControlData[QStringLiteral("��Сλ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("���λ��"), map_ControlData[QStringLiteral("���λ��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("λ��"), map_ControlData[QStringLiteral("λ��")].toString());
}

qstring krnl_SliderBar::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�������";
		break;
	case 1:
		ret = "�ɷ񱻹ر�";
		break;
	case 2:
		ret = "��������";
		break;
	case 3:
		ret = "λ�ñ��ı�";
		break;
	case 4:
		ret = "�ߴ类�ı�";
		break;
	case 5:
		ret = "������";
		break;
	case 6:
		ret = "��ȡ������";
		break;
	case 7:
		ret = "����";
		break;
	case 8:
		ret = "�״μ���";
		break;
	case 9:
		ret = "�����¼�";
		break;
	case 10:
		ret = "����ʾ";
		break;
	case 11:
		ret = "������";
		break;
	case 12:
		ret = "���ڿɷ񱻹ر�";
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

QString krnl_SliderBar::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/������.ico");
}
