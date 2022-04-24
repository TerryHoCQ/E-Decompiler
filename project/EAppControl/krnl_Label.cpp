#include "krnl_Label.h"
#include "../GuiParser.h"
#include "../ControlInfoWidget.h"
#include "../PropertyDelegate.h"
#include "../common/public.h"

struct Label_UnitData
{
	unsigned int version;
	unsigned int Ч��;
	unsigned int ����߿���;
	unsigned int �߿�;
	unsigned int ����߿���ɫ1;
	unsigned int ����߿���ɫ2;
	unsigned int ����߿���ɫ3;
	unsigned int �ı���ɫ;
	unsigned int ������ɫ;
	unsigned int ��ͼ��ʽ;
	unsigned int ���䱳����ʽ;
	unsigned int ���䱳����ɫ1;
	unsigned int ���䱳����ɫ2;
	unsigned int ���䱳����ɫ3;
	unsigned int ������뷽ʽ;
	unsigned int ������뷽ʽ;
	unsigned int �Ƿ��Զ�����;
	qvector<unsigned char> ����;
	qvector<unsigned char> ��ͼ;
	qstring ����;
	qstring ����Դ;
	qstring ������;
};

QStringList krnl_Label::ȡЧ���б�()
{
	QStringList Items = {
	QStringLiteral("ͨ��"),
	QStringLiteral("����"),
	QStringLiteral("͹��"),
	QStringLiteral("��Ӱ"),
	};
	return Items;
}

QStringList krnl_Label::ȡ��ͼ��ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("ͼƬ������"),
	QStringLiteral("ͼƬƽ��"),
	QStringLiteral("ͼƬ����"),
	};
	return Items;
}

QStringList krnl_Label::ȡ�߿��б�()
{
	QStringList Items = {
	QStringLiteral("�ޱ߿�"),
	QStringLiteral("����ʽ"),
	QStringLiteral("͹��ʽ"),
	QStringLiteral("ǳ����ʽ"),
	QStringLiteral("����ʽ"),
	QStringLiteral("���߱߿�ʽ"),
	QStringLiteral("���侵��ʽ"),
	};
	return Items;
}

QStringList krnl_Label::ȡ������뷽ʽ�б�()
{
	QStringList Items = {
		QStringLiteral("�����"),
		QStringLiteral("����"),
		QStringLiteral("�Ҷ���"),
	};
	return Items;
}

QStringList krnl_Label::ȡ������뷽ʽ�б�()
{
	QStringList Items = {
		QStringLiteral("������"),
		QStringLiteral("����"),
		QStringLiteral("�׶���"),
	};
	return Items;
}

QStringList krnl_Label::ȡ���䱳����ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("�޽��䱳��"),
	QStringLiteral("���ϵ���"),
	QStringLiteral("������"),
	QStringLiteral("�����ϵ�����"),
	QStringLiteral("�����ϵ�����"),
	QStringLiteral("���µ���"),
	QStringLiteral("���ҵ���"),
	QStringLiteral("�����µ�����"),
	QStringLiteral("�����µ�����"),
	};
	return Items;
}

QString krnl_Label::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/��ǩ.ico");
}

void krnl_Label::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("Ч��")] = 0;
	out_data[QStringLiteral("����߿���")] = 8;
	out_data[QStringLiteral("�߿�")] = 0;
	out_data[QStringLiteral("����߿���ɫ1")] = 0x808080;
	out_data[QStringLiteral("����߿���ɫ2")] = 0xFFFFFF;
	out_data[QStringLiteral("����߿���ɫ3")] = 0x808080;
	out_data[QStringLiteral("�ı���ɫ")] = 0x0;
	out_data[QStringLiteral("������ɫ")] = 0xFF000000;
	out_data[QStringLiteral("��ͼ��ʽ")] = 1;
	out_data[QStringLiteral("���䱳����ʽ")] = 0;
	out_data[QStringLiteral("���䱳����ɫ1")] = 0x808080;
	out_data[QStringLiteral("���䱳����ɫ2")] = 0xFFFFFF;
	out_data[QStringLiteral("���䱳����ɫ3")] = 0x808080;
	out_data[QStringLiteral("������뷽ʽ")] = 0;
	out_data[QStringLiteral("������뷽ʽ")] = 1;
	out_data[QStringLiteral("�Ƿ��Զ�����")] = 0;
	out_data[QStringLiteral("����")] = QStringLiteral("��ǩ");
}

void krnl_Label::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	Label_UnitData tmpData;
	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 2) {
		return;
	}

	tmpData.Ч�� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����߿��� = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);

	tmpData.����߿���ɫ1 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����߿���ɫ2 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.����߿���ɫ3 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�ı���ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������ɫ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.��ͼ��ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���䱳����ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���䱳����ɫ1 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���䱳����ɫ2 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.���䱳����ɫ3 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.������뷽ʽ = CDR_ReadUInt(pUnitDataPtr);
	tmpData.�Ƿ��Զ����� = CDR_ReadUInt(pUnitDataPtr);

	tmpData.���� = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.��ͼ = CDR_ReadCFreqMem(pUnitDataPtr);

	tmpData.���� = CDR_ReadCString(pUnitDataPtr);
	if (tmpData.version == 2) {
		tmpData.����Դ = CDR_ReadCString(pUnitDataPtr);
		tmpData.������ = CDR_ReadCString(pUnitDataPtr);
	}
	//����������������������������������������������������������������
	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("Ч��")] = tmpData.Ч��;
	out_data[QStringLiteral("����߿���")] = tmpData.����߿���;
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("����߿���ɫ1")] = tmpData.����߿���ɫ1;
	out_data[QStringLiteral("����߿���ɫ2")] = tmpData.����߿���ɫ2;
	out_data[QStringLiteral("����߿���ɫ3")] = tmpData.����߿���ɫ3;
	out_data[QStringLiteral("�ı���ɫ")] = tmpData.�ı���ɫ;
	out_data[QStringLiteral("������ɫ")] = tmpData.������ɫ;
	out_data[QStringLiteral("��ͼ��ʽ")] = tmpData.��ͼ��ʽ;
	out_data[QStringLiteral("���䱳����ʽ")] = tmpData.���䱳����ʽ;
	out_data[QStringLiteral("���䱳����ɫ1")] = tmpData.���䱳����ɫ1;
	out_data[QStringLiteral("���䱳����ɫ2")] = tmpData.���䱳����ɫ2;
	out_data[QStringLiteral("���䱳����ɫ3")] = tmpData.���䱳����ɫ3;
	out_data[QStringLiteral("������뷽ʽ")] = tmpData.������뷽ʽ;
	out_data[QStringLiteral("������뷽ʽ")] = tmpData.������뷽ʽ;
	out_data[QStringLiteral("�Ƿ��Զ�����")] = tmpData.�Ƿ��Զ�����;
	if (tmpData.����.size()) {
		out_data[QStringLiteral("����")] = QByteArray((char*)&tmpData.����[0], tmpData.����.size());
	}
	if (tmpData.��ͼ.size()) {
		out_data[QStringLiteral("��ͼ")] = QByteArray((char*)&tmpData.��ͼ[0], tmpData.��ͼ.size());
	}
	out_data[QStringLiteral("����")] = QString::fromLocal8Bit(tmpData.����.c_str());
	out_data[QStringLiteral("����Դ")] = QString::fromLocal8Bit(tmpData.����Դ.c_str());
	out_data[QStringLiteral("������")] = QString::fromLocal8Bit(tmpData.������.c_str());
	return;
}

void krnl_Label::��ӽ�����ɫ�ؼ�(QString ProperyName, unsigned int ProperyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);

	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(ProperyName,ui_LineEditor_ReadOnly));

	if (ProperyValue == 0xFF000000) {
		uint32 color = GetSysColor(COLOR_BTNFACE);
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral("͸��ɫ"), ui_ColorDialog));
		GuiParser::g_ControlInfoWindow->ui.ControlTable->item(insertRow, COLUMN_PropertyValue)->setBackgroundColor(QColor(GetRValue(color), GetGValue(color), GetBValue(color)));
	}
	else {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem("", ui_ColorDialog));
		GuiParser::g_ControlInfoWindow->ui.ControlTable->item(insertRow, COLUMN_PropertyValue)->setBackgroundColor(QColor(GetRValue(ProperyValue), GetGValue(ProperyValue), GetBValue(ProperyValue)));
	}
}

void krnl_Label::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::�����Ч�ؼ�(QStringLiteral("��ͣ������"), QStringLiteral("** ��Ч **"));
	EAppControl::����ı��ؼ�(QStringLiteral("    ͣ��˳��"), map_ControlData[QStringLiteral("ͣ��˳��")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("Ч��"), krnl_Label::ȡЧ���б�(), map_ControlData[QStringLiteral("Ч��")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), krnl_Label::ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("    ����߿���"), map_ControlData[QStringLiteral("����߿���")].toString());
	krnl_Label::��ӽ�����ɫ�ؼ�(QStringLiteral("����߿���ɫ1"), map_ControlData[QStringLiteral("����߿���ɫ1")].toUInt());
	krnl_Label::��ӽ�����ɫ�ؼ�(QStringLiteral("����߿���ɫ2"), map_ControlData[QStringLiteral("����߿���ɫ2")].toUInt());
	krnl_Label::��ӽ�����ɫ�ؼ�(QStringLiteral("����߿���ɫ3"), map_ControlData[QStringLiteral("����߿���ɫ3")].toUInt());
	EAppControl::�������ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toByteArray());
	EAppControl::�����ɫ�ؼ�(QStringLiteral("�ı���ɫ"), map_ControlData[QStringLiteral("�ı���ɫ")].toUInt());
	EAppControl::��ӵ�ɫ�ؼ�(QStringLiteral("������ɫ"), map_ControlData[QStringLiteral("������ɫ")].toUInt());
	EAppControl::���ͼƬ�ؼ�(QStringLiteral("��ͼ"), map_ControlData[QStringLiteral("��ͼ")].toByteArray());
	EAppControl::����б�ؼ�(QStringLiteral("    ��ͼ��ʽ"), krnl_Label::ȡ��ͼ��ʽ�б�(), map_ControlData[QStringLiteral("��ͼ��ʽ")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("���䱳����ʽ"), krnl_Label::ȡ���䱳����ʽ�б�(), map_ControlData[QStringLiteral("���䱳����ʽ")].toUInt());
	krnl_Label::��ӽ�����ɫ�ؼ�(QStringLiteral("���䱳����ɫ1"), map_ControlData[QStringLiteral("���䱳����ɫ1")].toUInt());
	krnl_Label::��ӽ�����ɫ�ؼ�(QStringLiteral("���䱳����ɫ2"), map_ControlData[QStringLiteral("���䱳����ɫ2")].toUInt());
	krnl_Label::��ӽ�����ɫ�ؼ�(QStringLiteral("���䱳����ɫ3"), map_ControlData[QStringLiteral("���䱳����ɫ3")].toUInt());
	EAppControl::����б�ؼ�(QStringLiteral("������뷽ʽ"), krnl_Label::ȡ������뷽ʽ�б�(), map_ControlData[QStringLiteral("������뷽ʽ")].toUInt());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�Ƿ��Զ�����"), map_ControlData[QStringLiteral("�Ƿ��Զ�����3")].toBool());
	EAppControl::����б�ؼ�(QStringLiteral("������뷽ʽ"), krnl_Label::ȡ������뷽ʽ�б�(), map_ControlData[QStringLiteral("������뷽ʽ")].toUInt());
	EAppControl::����ı��ؼ�(QStringLiteral("����Դ"), map_ControlData[QStringLiteral("����Դ")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("������"), map_ControlData[QStringLiteral("������")].toString());

	return;
}

qstring krnl_Label::ȡ�¼�����(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "�����¼�";
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