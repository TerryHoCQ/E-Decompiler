#include "krnl_window.h"
#include <bytes.hpp>
#include "../GuiParser.h"
#include "../ControlInfoWidget.h"
#include "../PropertyDelegate.h"
#include "../common/public.h"
#include <QtWidgets/QComboBox>

struct WinFrom_UnitData
{
	unsigned int version;
	unsigned int �߿�;
	unsigned int ��ͼ��ʽ;
	unsigned int ��ɫ;
	unsigned int ��󻯰�ť;
	unsigned int ��С����ť;
	unsigned int ���ư�ť;
	unsigned int λ��;
	unsigned int �ɷ��ƶ�;
	unsigned int ���Ŵ���;
	unsigned int �س����ƽ���;
	unsigned int Esc���ر�;
	unsigned int F1���򿪰���;
	unsigned int ������־ֵ;
	unsigned int ������������ʾ;
	unsigned int �����ƶ�;
	unsigned int ����;
	unsigned int ������ǰ;
	unsigned int ���ֱ���������;
	qstring ��������;
	qvector<unsigned char> ��ͼ;
	qvector<unsigned char> ͼ��;
	qvector<unsigned char> ��������;
	qstring ����;
	qstring �����ļ���;
};

QStringList ȡ��ͼ��ʽ�б�()
{
	QStringList Items = {
	QStringLiteral("ͼƬ������"),
	QStringLiteral("ͼƬƽ��"),
	QStringLiteral("ͼƬ����"),
	QStringLiteral("����ͼƬ"),
	};
	return Items;
}

QStringList ȡλ���б�()
{
	QStringList Items = {
		QStringLiteral("ͨ��"),
		QStringLiteral("����"),
		QStringLiteral("��С��"),
		QStringLiteral("���"),
	};
	return Items;
}

QStringList ȡ�����б�()
{
	QStringList Items = {
		QStringLiteral("����"),
		QStringLiteral("��Բ"),
		QStringLiteral("Բ�Ǿ���"),
		QStringLiteral("��"),
		QStringLiteral("������"),
		QStringLiteral("������"),
		QStringLiteral("������"),
		QStringLiteral("������"),
		QStringLiteral("ƽ���ı���"),
		QStringLiteral("�����"),
		QStringLiteral("������"),
		QStringLiteral("����"),
		QStringLiteral("����"),
		QStringLiteral("�����"),
		QStringLiteral("ʮ����"),
		QStringLiteral("������"),
		QStringLiteral("��ը��1"),
		QStringLiteral("��ը��2"),
		QStringLiteral("��β"),
		QStringLiteral("�۽Ǿ���"),
		QStringLiteral("���ͷ"),
		QStringLiteral("�Ҽ�ͷ"),
		QStringLiteral("�ϼ�ͷ"),
		QStringLiteral("�¼�ͷ"),
		QStringLiteral("���Ҽ�ͷ"),
		QStringLiteral("���¼�ͷ"),
		QStringLiteral("ʮ�ּ�ͷ"),
		QStringLiteral("���Ӽ�ͷ"),
		QStringLiteral("��β��ͷ"),
		QStringLiteral("����μ�ͷ"),
	};
	return Items;
}

QStringList ȡ���Ŵ����б�()
{
	QStringList Items = {
		QStringLiteral("ѭ������"),
		QStringLiteral("������һ��"),
		QStringLiteral("������"),
	};
	return Items;
}

QStringList ȡ�߿��б�()
{
	QStringList Items = {
		QStringLiteral("�ޱ߿�"),
		QStringLiteral("��ͨ�ɵ��߿�"),
		QStringLiteral("��ͨ�̶��߿�"),
		QStringLiteral("խ����ɵ��߿�"),
		QStringLiteral("խ����̶��߿�"),
		QStringLiteral("����ʽ�ɵ��߿�"),
		QStringLiteral("����ʽ�̶��߿�"),
	};
	return Items;
}

void krnl_window::��ӱ������ֿؼ�(QByteArray& ProperyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);

	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(QStringLiteral("��������")));
	if (ProperyValue.size()) {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral("������")));
	}
	else {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral("")));
	}
	return;
}


QString krnl_window::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/Window.ico");
}

void krnl_window::ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("version")] = 6;
	out_data[QStringLiteral("�߿�")] = 2;
	out_data[QStringLiteral("��ɫ")] = 0xFF000000;
	out_data[QStringLiteral("��ͼ��ʽ")] = 1;
	out_data[QStringLiteral("���Ŵ���")] = 0;
	out_data[QStringLiteral("���ư�ť")] = 1;
	out_data[QStringLiteral("��󻯰�ť")] = 0;
	out_data[QStringLiteral("��С����ť")] = 1;
	out_data[QStringLiteral("λ��")] = 1;
	out_data[QStringLiteral("�ɷ��ƶ�")] = 1;
	out_data[QStringLiteral("�س����ƽ���")] = 0;
	out_data[QStringLiteral("Esc���ر�")] = 1;
	out_data[QStringLiteral("F1���򿪰���")] = 0;
	out_data[QStringLiteral("������������ʾ")] = 1;
	out_data[QStringLiteral("�����ƶ�")] = 0;
	out_data[QStringLiteral("����")] = 0;
	out_data[QStringLiteral("������ǰ")] = 0;
	out_data[QStringLiteral("���ֱ���������")] = 0;
}

void krnl_window::�����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	WinFrom_UnitData tmpData;
	tmpData.version = CDR_ReadUInt(pUnitDataPtr);

	if (tmpData.version <= 6) {
		tmpData.�߿� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.��ͼ��ʽ = CDR_ReadUInt(pUnitDataPtr);
		tmpData.��ɫ = CDR_ReadUInt(pUnitDataPtr);
		tmpData.��󻯰�ť = CDR_ReadUInt(pUnitDataPtr);
		tmpData.��С����ť = CDR_ReadUInt(pUnitDataPtr);
		tmpData.���ư�ť = CDR_ReadUInt(pUnitDataPtr);
		tmpData.λ�� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.�ɷ��ƶ� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.���Ŵ��� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.�س����ƽ��� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.Esc���ر� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.F1���򿪰��� = CDR_ReadUInt(pUnitDataPtr);
		tmpData.������־ֵ = CDR_ReadUInt(pUnitDataPtr);

		if (tmpData.version >= 2) {
			tmpData.������������ʾ = CDR_ReadUInt(pUnitDataPtr);
		}
		if (tmpData.version >= 3) {
			tmpData.�����ƶ� = CDR_ReadUInt(pUnitDataPtr);
			tmpData.���� = CDR_ReadUInt(pUnitDataPtr);
		}
		if (tmpData.version >= 4) {
			tmpData.������ǰ = CDR_ReadUInt(pUnitDataPtr);
		}
		if (tmpData.version >= 5) {
			tmpData.���ֱ��������� = CDR_ReadUInt(pUnitDataPtr);
		}
		if (tmpData.version == 6) {
			tmpData.�������� = CDR_ReadCString(pUnitDataPtr);
		}

		tmpData.��ͼ = CDR_ReadCFreqMem(pUnitDataPtr);
		tmpData.ͼ�� = CDR_ReadCFreqMem(pUnitDataPtr);
		tmpData.�������� = CDR_ReadCFreqMem(pUnitDataPtr);

		tmpData.���� = CDR_ReadCString(pUnitDataPtr);
		tmpData.�����ļ��� = CDR_ReadCString(pUnitDataPtr);
	}

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("�߿�")] = tmpData.�߿�;
	out_data[QStringLiteral("��ͼ��ʽ")] = tmpData.��ͼ��ʽ;
	out_data[QStringLiteral("��ɫ")] = tmpData.��ɫ;
	out_data[QStringLiteral("��󻯰�ť")] = tmpData.��С����ť;
	out_data[QStringLiteral("���ư�ť")] = tmpData.���ư�ť;
	out_data[QStringLiteral("λ��")] = tmpData.λ��;
	out_data[QStringLiteral("�ɷ��ƶ�")] = tmpData.�ɷ��ƶ�;
	out_data[QStringLiteral("���Ŵ���")] = tmpData.���Ŵ���;
	out_data[QStringLiteral("�س����ƽ���")] = tmpData.�س����ƽ���;
	out_data[QStringLiteral("Esc���ر�")] = tmpData.Esc���ر�;
	out_data[QStringLiteral("F1���򿪰���")] = tmpData.F1���򿪰���;
	out_data[QStringLiteral("������־ֵ")] = tmpData.������־ֵ;
	out_data[QStringLiteral("������������ʾ")] = tmpData.������������ʾ;
	out_data[QStringLiteral("�����ƶ�")] = tmpData.�����ƶ�;
	out_data[QStringLiteral("����")] = tmpData.����;
	out_data[QStringLiteral("������ǰ")] = tmpData.������ǰ;
	out_data[QStringLiteral("���ֱ���������")] = tmpData.���ֱ���������;
	out_data[QStringLiteral("��������")] = QString::fromLocal8Bit(tmpData.��������.c_str());

	if (tmpData.��ͼ.size()) {
		out_data[QStringLiteral("��ͼ")] = QByteArray((char*)&tmpData.��ͼ[0], tmpData.��ͼ.size());
	}
	if (tmpData.ͼ��.size()) {
		out_data[QStringLiteral("ͼ��")] = QByteArray((char*)&tmpData.ͼ��[0], tmpData.ͼ��.size());
	}
	if (tmpData.��������.size()) {
		out_data[QStringLiteral("��������")] = QByteArray((char*)&tmpData.��������[0], tmpData.��������.size());
	}

	out_data[QStringLiteral("����")] = QString::fromLocal8Bit(tmpData.����.c_str());
	out_data[QStringLiteral("�����ļ���")] = QString::fromLocal8Bit(tmpData.�����ļ���.c_str());
	return;
}

void krnl_window::��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::����ı��ؼ�(QStringLiteral("����"), map_ControlData[QStringLiteral("����")].toString());
	EAppControl::����б�ؼ�(QStringLiteral("�߿�"), ȡ�߿��б�(), map_ControlData[QStringLiteral("�߿�")].toUInt());
	EAppControl::��ӵ�ɫ�ؼ�(QStringLiteral("��ɫ"), map_ControlData[QStringLiteral("��ɫ")].toUInt());
	EAppControl::���ͼƬ�ؼ�(QStringLiteral("��ͼ"), map_ControlData[QStringLiteral("��ͼ")].toByteArray());
	EAppControl::����б�ؼ�(QStringLiteral("    ��ͼ��ʽ"), ȡ��ͼ��ʽ�б�(), map_ControlData[QStringLiteral("��ͼ��ʽ")].toUInt());
	krnl_window::��ӱ������ֿؼ�(map_ControlData[QStringLiteral("��������")].toByteArray());
	EAppControl::����б�ؼ�(QStringLiteral("    ���Ŵ���"), ȡ���Ŵ����б�(), map_ControlData[QStringLiteral("���Ŵ���")].toUInt());

	EAppControl::��Ӳ����ؼ�(QStringLiteral("���ư�ť"), map_ControlData[QStringLiteral("���ư�ť")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("    ��󻯰�ť"), map_ControlData[QStringLiteral("��󻯰�ť")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("    ��С����ť"), map_ControlData[QStringLiteral("��С����ť")].toBool());

	EAppControl::����б�ؼ�(QStringLiteral("λ��"), ȡλ���б�(), map_ControlData[QStringLiteral("λ��")].toUInt());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�ɷ��ƶ�"), map_ControlData[QStringLiteral("�ɷ��ƶ�")].toBool());
	EAppControl::���ͼƬ�ؼ�(QStringLiteral("ͼ��"), map_ControlData[QStringLiteral("ͼ��")].toByteArray());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�س����ƽ���"), map_ControlData[QStringLiteral("�س����ƽ���")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("Esc���ر�"), map_ControlData[QStringLiteral("Esc���ر�")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("F1���򿪰���"), map_ControlData[QStringLiteral("F1���򿪰���")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("    �����ļ���"), map_ControlData[QStringLiteral("�����ļ���")].toString());
	EAppControl::����ı��ؼ�(QStringLiteral("    ������־ֵ"), map_ControlData[QStringLiteral("������־ֵ")].toString());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("������������ʾ"), map_ControlData[QStringLiteral("������������ʾ")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("�����ƶ�"), map_ControlData[QStringLiteral("�����ƶ�")].toBool());
	EAppControl::����б�ؼ�(QStringLiteral("����"), ȡ�����б�(), map_ControlData[QStringLiteral("����")].toUInt());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("������ǰ"), map_ControlData[QStringLiteral("������ǰ")].toBool());
	EAppControl::��Ӳ����ؼ�(QStringLiteral("���ֱ���������"), map_ControlData[QStringLiteral("���ֱ���������")].toBool());
	EAppControl::����ı��ؼ�(QStringLiteral("��������"), map_ControlData[QStringLiteral("��������")].toString());
	return;
}

qstring krnl_window::ȡ�¼�����(int eventIndex)
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
	default:
		ret = "δ֪�¼�";
		break;
	}
	return ret;
}