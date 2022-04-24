#include "krnl_DrawPanel.h"
#include "../common/public.h"

struct DrawPanel_UnitData
{
	unsigned int version;
	unsigned int �߿�;
	unsigned int ���屳��ɫ;
	unsigned int ��ͼ��ʽ;
	unsigned int �Զ��ػ�;
	unsigned int �滭��λ;
	unsigned int ��������;
	unsigned int ������ʽ;
	unsigned int ���ʴ�ϸ;
	unsigned int ������ɫ;
	unsigned int ˢ������;
	unsigned int ˢ����ɫ;
	unsigned int �ı���ɫ;
	unsigned int �ı�������ɫ;
	qvector<unsigned char> ����;
	qvector<unsigned char> ��ͼ;
};

QStringList krnl_DrawPanel::ȡ�߿��б�()
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

QStringList krnl_DrawPanel::ȡ��ͼ��ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("ͼƬ������"),
	QStringLiteral("ͼƬƽ��"),
	QStringLiteral("ͼƬ����"),
	};
	return Items;
}

QStringList krnl_DrawPanel::ȡ�滭��λ�б�()
{
	QStringList Items = {
	QStringLiteral("���ص�"),
	QStringLiteral("0.1����"),
	QStringLiteral("0.01����"),
	QStringLiteral("0.01Ӣ��"),
	QStringLiteral("0.001Ӣ��"),
	QStringLiteral("1/1440Ӣ��"),
	};
	return Items;
}

QStringList krnl_DrawPanel::ȡ���������б�()
{
	QStringList Items = {
	QStringLiteral("�ձ�"),
	QStringLiteral("ֱ��"),
	QStringLiteral("����"),
	QStringLiteral("����"),
	QStringLiteral("�㻮��"),
	QStringLiteral("˫�㻮��"),
	QStringLiteral("��ֱ��"),
	};
	return Items;
}

QStringList krnl_DrawPanel::ȡ������ʽ�б�()
{
	QStringList Items = {
		QStringLiteral("��ɫ"),
		QStringLiteral("�ǻ��"),
		QStringLiteral("��Ǳ�"),
		QStringLiteral("�Ǹ��Ʊ�"),
		QStringLiteral("��ʷ�"),
		QStringLiteral("��ת"),
		QStringLiteral("����"),
		QStringLiteral("�����"),
		QStringLiteral("���"),
		QStringLiteral("������"),
		QStringLiteral("�޲���"),
		QStringLiteral("��Ǳ�"),
		QStringLiteral("���Ʊ�"),
		QStringLiteral("��ʷ�"),
		QStringLiteral("���"),
		QStringLiteral("��ɫ"),
	};
	return Items;
}

QStringList krnl_DrawPanel::ȡˢ�������б�()
{
	QStringList Items = {
		QStringLiteral("��ˢ��"),//0
		QStringLiteral("��ɫˢ��"),//1
		QStringLiteral("��б��"),//2
		QStringLiteral("ֱ������"),//3
		QStringLiteral("б������"),//4
		QStringLiteral("��б��"),//5
		QStringLiteral("����"),//6
		QStringLiteral("����"),//7
		QStringLiteral("5%ɫ��"),//8
		QStringLiteral("10%ɫ��"),//9
		QStringLiteral("20%ɫ��"),//10
		QStringLiteral("25%ɫ��"),//11
		QStringLiteral("30%ɫ��"),//12
		QStringLiteral("40%ɫ��"),//13
		QStringLiteral("50%ɫ��"),//14
		QStringLiteral("60%ɫ��"),//15
		QStringLiteral("70%ɫ��"),//16
		QStringLiteral("75%ɫ��"),//17
		QStringLiteral("80%ɫ��"),//18
		QStringLiteral("90%ɫ��"),//19
		QStringLiteral("ǳɫ�϶Խ���"),//20
		QStringLiteral("ǳɫ�¶Խ���"),//21
		QStringLiteral("��ɫ�϶Խ���"),//22
		QStringLiteral("��ɫ�¶Խ���"),//23
		QStringLiteral("���϶Խ���"),//24
		QStringLiteral("���¶Խ���"),//25
		QStringLiteral("ǳɫ����"),//26
		QStringLiteral("ǳɫ����"),//27
		QStringLiteral("խ����"),//28
		QStringLiteral("խ����"),//29
		QStringLiteral("��ɫ����"),//30
		QStringLiteral("��ɫ����"),//31
		QStringLiteral("�϶Խ�����"),//32
		QStringLiteral("�¶Խ�����"),//33
		QStringLiteral("������"),//34
		QStringLiteral("������"),//35
		QStringLiteral("Сֽм"),//36
		QStringLiteral("��ֽм"),//37
		QStringLiteral("֮����"),//38
		QStringLiteral("������"),//39
		QStringLiteral("�Խ�ש��"),//40
		QStringLiteral("����ש��"),//41
		QStringLiteral("��֯��"),//42
		QStringLiteral("������"),//43
		QStringLiteral("��Ƥ"),//44
		QStringLiteral("�����"),//45
		QStringLiteral("��ʽ����"),//46
		QStringLiteral("����"),//47
		QStringLiteral("���"),//48
		QStringLiteral("����"),//49
		QStringLiteral("С����"),//50
		QStringLiteral("������"),//51
		QStringLiteral("С����"),//52
		QStringLiteral("������"),//53
		QStringLiteral("��������"),//54
		QStringLiteral("ʵ������"),//55
	};
	return Items;
}

void krnl_DrawPanel::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("�߿�")] = 0x0;
	out_data[QStringLiteral("���屳��ɫ")] = 0xFF000000;
	out_data[QStringLiteral("��ͼ��ʽ")] = 0x1;
	out_data[QStringLiteral("�Զ��ػ�")] = 0x0;
	out_data[QStringLiteral("�滭��λ")] = 0x0;
	out_data[QStringLiteral("��������")] = 0x1;
	out_data[QStringLiteral("������ʽ")] = 0xC;
	out_data[QStringLiteral("���ʴ�ϸ")] = 0x0;
	out_data[QStringLiteral("������ɫ")] = 0x0;
	out_data[QStringLiteral("ˢ������")] = 0x1;
	out_data[QStringLiteral("ˢ����ɫ")] = 0xFFFFFF;
	out_data[QStringLiteral("�ı���ɫ")] = 0x0;
	out_data[QStringLiteral("�ı�������ɫ")] = 0xFF000000;
}

void krnl_DrawPanel::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	DrawPanel_UnitData tmpData;
	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���屳��ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ͼ��ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�Զ��ػ� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�滭��λ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�������� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���ʴ�ϸ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ˢ������ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.ˢ����ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�ı���ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�ı�������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.��ͼ = CDR_ReadCFreqMem(pUnitDataPtr);

	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("���屳��ɫ")] = tmpData.���屳��ɫ;
	out_data[QStringLiteral("��ͼ��ʽ")] = tmpData.��ͼ��ʽ;
	out_data[QStringLiteral("�Զ��ػ�")] = tmpData.�Զ��ػ�;
	out_data[QStringLiteral("�滭��λ")] = tmpData.�滭��λ;
	out_data[QStringLiteral("��������")] = tmpData.��������;
	out_data[QStringLiteral("������ʽ")] = tmpData.������ʽ;
	out_data[QStringLiteral("���ʴ�ϸ")] = tmpData.���ʴ�ϸ;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	out_data[QStringLiteral("ˢ������")] = tmpData.ˢ������;
	out_data[QStringLiteral("ˢ����ɫ")] = tmpData.ˢ����ɫ;
	out_data[QStringLiteral("�ı���ɫ")] = tmpData.�ı���ɫ;
	out_data[QStringLiteral("�ı���ɫ")] = tmpData.�ı���ɫ;
	out_data[QStringLiteral("�ı�������ɫ")] = tmpData.�ı�������ɫ;
	
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	if (tmpData.��ͼ.size()) {
		out_data[QStringLiteral("��ͼ")] = QByteArray((char*)&tmpData.��ͼ[0], tmpData.��ͼ.size());
	}
	return;
}

void krnl_DrawPanel::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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

	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), krnl_DrawPanel::ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("���屳��ɫ"), map_ControlData[QStringLiteral("���屳��ɫ")].toUInt());
	EAppControl::���ͼƬ�ؼ�(QStringLiteral("��ͼ"), map_ControlData[QStringLiteral("��ͼ")].toByteArray());
	EAppControl::����б�ؼ�(QStringLiteral("    ��ͼ��ʽ"), krnl_DrawPanel::ȡ��ͼ��ʽ�б�(), map_ControlData[QStringLiteral("��ͼ��ʽ")].toUInt());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�Զ��ػ�"), map_ControlData[QStringLiteral("�Զ��ػ�")].toBool());
	EAppControl::����б�ؼ�(QStringLiteral("�滭��λ"), krnl_DrawPanel::ȡ�滭��λ�б�(), map_ControlData[QStringLiteral("�滭��λ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("��������"), krnl_DrawPanel::ȡ���������б�(), map_ControlData[QStringLiteral("��������")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("������ʽ"), krnl_DrawPanel::ȡ������ʽ�б�(), map_ControlData[QStringLiteral("������ʽ")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("���ʴ�ϸ"), map_ControlData[QStringLiteral("���ʴ�ϸ")].toString());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("ˢ������"), krnl_DrawPanel::ȡˢ�������б�(), map_ControlData[QStringLiteral("ˢ������")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("ˢ����ɫ"), map_ControlData[QStringLiteral("ˢ����ɫ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�ı���ɫ"), map_ControlData[QStringLiteral("�ı���ɫ")].toUInt());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�ı�������ɫ"), map_ControlData[QStringLiteral("�ı�������ɫ")].toUInt());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
}

qstring krnl_DrawPanel::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�滭";
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

QString krnl_DrawPanel::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/����.ico");
}