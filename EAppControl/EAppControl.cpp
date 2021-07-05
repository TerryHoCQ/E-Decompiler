#include "EAppControl.h"
#include "../ControlInfoWidget.h"
#include <QMap>
#include "../GuiParser.h"
#include "../PropertyDelegate.h"
#include <bytes.hpp>
#include "../common/public.h"
#include "krnl_window.h"
#include "krnl_Button.h"
#include "krnl_Timer.h"
#include "krnl_ListBox.h"
#include "krnl_RadioBox.h"
#include "krnl_PicBtn.h"
#include "krnl_EditBox.h"
#include "krnl_PicBox.h"
#include "krnl_ShapeBox.h"
#include "krnl_CheckBox.h"
#include "krnl_DropTarget.h"
#include "EAppControlFactory.h"

unsigned char* EAppControl::GetUnitDataPtr(unsigned char* propertyAddr)
{
	unsigned char* ret = propertyAddr;
	ret += 0x18;
	ret += qstrlen(ret) + 1;
	ret += qstrlen(ret) + 1;
	ret += 0x1C;
	ret += (ReadUInt(ret) + 1) * 4;
	ret += ReadUInt(ret) + 4;
	ret += qstrlen(ret) + 1;
	ret += 0xC;
	ret += ReadUInt(ret) * 8;
	ret += 0x18;
	return ret;
}

QString ȡ���ָ������(unsigned int index)
{
	QString ret;
	switch (index)
	{
	case 0x0:
		ret = QStringLiteral("Ĭ����");
		break;
	case 0x00007F00:
		ret = QStringLiteral("��׼��ͷ��");
		break;
	case 0x00007F03:
		ret = QStringLiteral("ʮ����");
		break;
	case 0x00007F01:
		ret = QStringLiteral("�ı��༭��");
		break;
	case 0x00007F02:
		ret = QStringLiteral("ɳ©��");
		break;
	case 0x00007F8B:
		ret = QStringLiteral("��ͷ���ʺ���");
		break;
	case 0x00007F8A:
		ret = QStringLiteral("��ͷ��ɳ©��");
		break;
	case 0x00007F88:
		ret = QStringLiteral("��ֹ����");
		break;
	case 0x00007F86:
		ret = QStringLiteral("�����ͷ��");
		break;
	case 0x00007F83:
		ret = QStringLiteral("��<->����ͷ��");
		break;
	case 0x00007F85:
		ret = QStringLiteral("��<->�ϼ�ͷ��");
		break;
	case 0x00007F82:
		ret = QStringLiteral("��<->����ͷ��");
		break;
	case 0x00007F84:
		ret = QStringLiteral("��<->����ͷ��");
		break;
	case 0x00007F04:
		ret = QStringLiteral("���ϼ�ͷ��");
		break;
	case 0x00007F89:
		ret = QStringLiteral("����");
		break;
	case 0xFFFFFFFF:
		ret = QStringLiteral("�Զ�����");
		break;
	default:
		ret = QStringLiteral("δ֪");
		break;
	}

	return ret;
}

void EAppControl::�����ؼ���������(unsigned char* lpControlInfo, QHash<QString, QVariant>& map_ControlData)
{
	map_ControlData["�ؼ�ID"] = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	//�̶���20�����ֽ�,����ʹ��?
	lpControlInfo += 20;

	map_ControlData[QStringLiteral("����")] = QString::fromLocal8Bit(ReadStr(lpControlInfo).c_str());
	lpControlInfo += qstrlen(lpControlInfo) + 1;

	//�����ַ���?
	ReadStr(lpControlInfo);
	lpControlInfo += qstrlen(lpControlInfo) + 1;

	//�洢����?
	ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	map_ControlData[QStringLiteral("���")] = ReadInt(lpControlInfo);
	lpControlInfo += 4;

	map_ControlData[QStringLiteral("����")] = ReadInt(lpControlInfo);
	lpControlInfo += 4;

	map_ControlData[QStringLiteral("���")] = ReadInt(lpControlInfo);
	lpControlInfo += 4;

	map_ControlData[QStringLiteral("�߶�")] = ReadInt(lpControlInfo);
	lpControlInfo += 4;

	//ֵΪ0,�����洢LoadCursorA���صľ��ֵ��
	lpControlInfo += 4;

	//���ؼ�ID
	map_ControlData[QStringLiteral("���ؼ�ID")] = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	//�ӿؼ���Ŀ
	unsigned int childControlCount = ReadUInt(lpControlInfo);
	lpControlInfo += 4;
	for (unsigned int n = 0; n < childControlCount; ++n) {
		unsigned int tmpChildControlId = ReadUInt(lpControlInfo);
		lpControlInfo += 4;
	}

	//���ָ���С
	unsigned int CursorSize = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	map_ControlData[QStringLiteral("���ָ��")] = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	if (CursorSize > 4) {
		map_ControlData[QStringLiteral("���ָ������")] = QByteArray((char*)lpControlInfo, CursorSize);
		lpControlInfo += CursorSize - 4;
	}

	map_ControlData[QStringLiteral("���")] = QString::fromLocal8Bit(ReadStr(lpControlInfo).c_str());
	lpControlInfo += qstrlen(lpControlInfo) + 1;

	//δ֪��ֵ
	unsigned int unKnowValueA = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	unsigned int windowFlags = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	map_ControlData[QStringLiteral("����")] = windowFlags & 0x1;
	map_ControlData[QStringLiteral("��ֹ")] = windowFlags & 0x2;
	map_ControlData[QStringLiteral("��ͣ������")] = windowFlags & 0x4;

	map_ControlData[QStringLiteral("ͣ��˳��")] = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	unsigned int index2 = ReadUInt(lpControlInfo);
	lpControlInfo += 4;
	lpControlInfo += (index2 * 8) + 0x14;

	return;
}

QString EAppControl::ȡͼ����Դ·��()
{
	return QStringLiteral(":/ICO/ICO/Unknow.ico");
}

void EAppControl::��ʾ�ؼ���Ϣ(ControlType_t type, unsigned int propertyAddr, int propertySize)
{
	QHash<QString, QVariant> map_ControlData;
	qvector<unsigned char> tmpBuf;
	tmpBuf.resize(propertySize);
	get_bytes(&tmpBuf[0], propertySize, propertyAddr);

	if (type == krnl_menu) {

	}
	else {
		EAppControl::�����ؼ���������(&tmpBuf[0], map_ControlData);
	}
	
	EAppControl* pEAppControl = EAppControlFactory::getEAppControl(type);
	if (!pEAppControl) {
		return;
	}

	unsigned char* pUnitDataPtr = EAppControl::GetUnitDataPtr(&tmpBuf[0]);
	int UnitDataSize = (&tmpBuf[0] - pUnitDataPtr) + propertySize;
	if (!UnitDataSize) {
		pEAppControl->ȡ�ؼ�Ĭ�ϸ�������(map_ControlData);
	}
	else {
		pEAppControl->�����л��ؼ���������(pUnitDataPtr, map_ControlData);
	}

	pEAppControl->��ʾ�ؼ�������Ϣ(map_ControlData);
	return;
}

void EAppControl::����ı��ؼ�(QString PropertyName, QString PropertyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);

	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(PropertyName, ui_LineEditor_ReadOnly));
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(PropertyValue));
}

void EAppControl::����б�ؼ�(QString PropertyName, QStringList& PropertyList, unsigned int PropertyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(PropertyName, ui_LineEditor_ReadOnly));
	QComboBox* pComboBox = new QComboBox();
	pComboBox->setEditable(false);

	pComboBox->addItems(PropertyList);
	pComboBox->setCurrentIndex(PropertyValue);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setCellWidget(insertRow, COLUMN_PropertyValue, pComboBox);
	return;
}

void EAppControl::�����Ч�ؼ�(QString PropertyName,QString PropertyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(PropertyName, ui_LineEditor_ReadOnly));
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(PropertyValue, ui_LineEditor_Disabled));
	return;
}

void EAppControl::�������ؼ�(QString PropertyName, QByteArray& PropertyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(PropertyName, ui_LineEditor_ReadOnly));

	if (PropertyValue.size()) {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral("������"), ui_LineEditor_ReadOnly));
	}
	else {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral(""), ui_LineEditor_ReadOnly));
	}
}

void EAppControl::��ӵ�ɫ�ؼ�(QString propertyName, unsigned int ProperyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);

	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(propertyName, ui_LineEditor_ReadOnly));

	if (ProperyValue == 0xFF000000) {
		uint32 color = GetSysColor(COLOR_BTNFACE);
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral("Ĭ�ϵ�ɫ"), ui_ColorDialog));
		GuiParser::g_ControlInfoWindow->ui.ControlTable->item(insertRow, COLUMN_PropertyValue)->setBackgroundColor(QColor(GetRValue(color), GetGValue(color), GetBValue(color)));
	}
	else {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem("", ui_ColorDialog));
		GuiParser::g_ControlInfoWindow->ui.ControlTable->item(insertRow, COLUMN_PropertyValue)->setBackgroundColor(QColor(GetRValue(ProperyValue), GetGValue(ProperyValue), GetBValue(ProperyValue)));
	}
}

void EAppControl::�����ɫ�ؼ�(QString PropertyName, unsigned int PropertyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(PropertyName, ui_LineEditor_ReadOnly));
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral(""), ui_ColorDialog));
	if (PropertyValue == 0xFF000000) {
		uint32 color = GetSysColor(COLOR_BTNFACE);
		GuiParser::g_ControlInfoWindow->ui.ControlTable->item(insertRow, COLUMN_PropertyValue)->setBackgroundColor(QColor(GetRValue(color), GetGValue(color), GetBValue(color)));
	}
	else {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->item(insertRow, COLUMN_PropertyValue)->setBackgroundColor(QColor(GetRValue(PropertyValue), GetGValue(PropertyValue), GetBValue(PropertyValue)));
	}
}

void EAppControl::���ͼƬ�ؼ�(QString PropertyName, QByteArray& PropertyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(PropertyName));

	if (PropertyValue.size()) {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral("������"), ui_ImageBox));
	}
	else {
		GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyValue, new QTableWidgetItem(QStringLiteral(""), ui_ImageBox));
	}

	QImage image = QImage::fromData(PropertyValue);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->item(insertRow, COLUMN_PropertyValue)->setData(Qt::UserRole, image);
	return;
}

void EAppControl::������ؼ�(unsigned int ProperyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);

	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(QStringLiteral("���ָ��")));
	QComboBox* pComboBox = new QComboBox();
	pComboBox->setEditable(false);

	QStringList Items = {
		QStringLiteral("Ĭ����"),
		QStringLiteral("��׼��ͷ��"),
		QStringLiteral("ʮ����"),
		QStringLiteral("�ı��༭��"),
		QStringLiteral("ɳ©��"),
		QStringLiteral("��ͷ���ʺ���"),
		QStringLiteral("��ͷ��ɳ©��"),
		QStringLiteral("��ֹ����"),
		QStringLiteral("�����ͷ��"),
		QStringLiteral("��<->����ͷ��"),
		QStringLiteral("��<->�ϼ�ͷ��"),
		QStringLiteral("��<->����ͷ��"),
		QStringLiteral("��<->����ͷ��"),
		QStringLiteral("���ϼ�ͷ��"),
		QStringLiteral("����"),
		QStringLiteral("�Զ�����"),
	};
	pComboBox->addItems(Items);
	pComboBox->setCurrentText(ȡ���ָ������(ProperyValue));
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setCellWidget(insertRow, COLUMN_PropertyValue, pComboBox);
}

void EAppControl::��Ӳ����ؼ�(QString PropertyName, bool ProperyValue)
{
	int insertRow = GuiParser::g_ControlInfoWindow->ui.ControlTable->rowCount();
	GuiParser::g_ControlInfoWindow->ui.ControlTable->insertRow(insertRow);

	GuiParser::g_ControlInfoWindow->ui.ControlTable->setItem(insertRow, COLUMN_PropertyName, new QTableWidgetItem(PropertyName, ui_LineEditor_ReadOnly));
	QComboBox* pComboBox = new QComboBox();
	pComboBox->setEditable(false);
	pComboBox->addItem(QStringLiteral("��"));
	pComboBox->addItem(QStringLiteral("��"));
	pComboBox->setCurrentIndex(!ProperyValue);
	GuiParser::g_ControlInfoWindow->ui.ControlTable->setCellWidget(insertRow, COLUMN_PropertyValue, pComboBox);
}