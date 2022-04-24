#include "krnl_ProcessBar.h"
#include "../common/public.h"

struct ProcessBar_UnitData
{
	unsigned int version;
	unsigned int 边框;
	unsigned int 方向;
	unsigned int 显示方式;
	unsigned int 最小位置;
	unsigned int 最大位置;
	unsigned int 位置;
};

QStringList krnl_ProcessBar::取边框列表()
{
	QStringList Items = {
		QStringLiteral("无边框"),
		QStringLiteral("凹入式"),
		QStringLiteral("凸出式"),
		QStringLiteral("浅凹入式"),
		QStringLiteral("镜框式"),
		QStringLiteral("单线边框式"),
	};
	return Items;
}

QStringList krnl_ProcessBar::取方向列表()
{
	QStringList Items = {
		QStringLiteral("横向"),
		QStringLiteral("纵向"),
	};
	return Items;
}

QStringList krnl_ProcessBar::取显示方式列表()
{
	QStringList Items = {
		QStringLiteral("分块"),
		QStringLiteral("连续"),
	};
	return Items;

}

void krnl_ProcessBar::取控件默认附加属性(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("边框")] = 1;
	out_data[QStringLiteral("最大位置")] = 100;
	out_data[QStringLiteral("页改变值")] = 10;
	out_data[QStringLiteral("行改变值")] = 1;
	out_data[QStringLiteral("位置")] = 1;
	out_data[QStringLiteral("允许拖动跟踪")] = 1;
}

void krnl_ProcessBar::反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	ProcessBar_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.边框 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.方向 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.显示方式 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.最小位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.最大位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.位置 = CDR_ReadUInt(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("边框")] = tmpData.边框;
	out_data[QStringLiteral("方向")] = tmpData.方向;
	out_data[QStringLiteral("显示方式")] = tmpData.显示方式;
	out_data[QStringLiteral("最小位置")] = tmpData.最小位置;
	out_data[QStringLiteral("最大位置")] = tmpData.最大位置;
	out_data[QStringLiteral("位置")] = tmpData.位置;
}

void krnl_ProcessBar::显示控件属性信息(QHash<QString, QVariant>& map_ControlData)
{
	EAppControl::添加文本控件(QStringLiteral("名称"), map_ControlData[QStringLiteral("名称")].toString());
	EAppControl::添加文本控件(QStringLiteral("左边"), map_ControlData[QStringLiteral("左边")].toString());
	EAppControl::添加文本控件(QStringLiteral("顶边"), map_ControlData[QStringLiteral("顶边")].toString());
	EAppControl::添加文本控件(QStringLiteral("宽度"), map_ControlData[QStringLiteral("宽度")].toString());
	EAppControl::添加文本控件(QStringLiteral("高度"), map_ControlData[QStringLiteral("高度")].toString());
	EAppControl::添加文本控件(QStringLiteral("标记"), map_ControlData[QStringLiteral("标记")].toString());
	EAppControl::添加布尔控件(QStringLiteral("可视"), map_ControlData[QStringLiteral("可视")].toBool());
	EAppControl::添加布尔控件(QStringLiteral("禁止"), map_ControlData[QStringLiteral("禁止")].toBool());
	EAppControl::添加鼠标控件(map_ControlData[QStringLiteral("鼠标指针")].toUInt());
	EAppControl::添加列表控件(QStringLiteral("边框"), krnl_ProcessBar::取边框列表(), map_ControlData[QStringLiteral("边框")].toUInt());
	EAppControl::添加列表控件(QStringLiteral("方向"), krnl_ProcessBar::取方向列表(), map_ControlData[QStringLiteral("方向")].toUInt());
	EAppControl::添加列表控件(QStringLiteral("显示方式"), krnl_ProcessBar::取显示方式列表(), map_ControlData[QStringLiteral("显示方式")].toUInt());
	EAppControl::添加文本控件(QStringLiteral("最小位置"), map_ControlData[QStringLiteral("最小位置")].toString());
	EAppControl::添加文本控件(QStringLiteral("最大位置"), map_ControlData[QStringLiteral("最大位置")].toString());
	EAppControl::添加文本控件(QStringLiteral("位置"), map_ControlData[QStringLiteral("位置")].toString());
}

qstring krnl_ProcessBar::取事件名称(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case -1:
		ret = "鼠标左键被按下";
		break;
	case -2:
		ret = "鼠标左键被放开";
		break;
	case -3:
		ret = "被双击";
		break;
	case -4:
		ret = "鼠标右键被按下";
		break;
	case -5:
		ret = "鼠标右键被放开";
		break;
	case -6:
		ret = "鼠标位置被移动";
		break;
	case -12:
		ret = "滚轮被滚动";
		break;
	default:
		ret = "未知事件";
		break;
	}

	return ret;
}

QString krnl_ProcessBar::取图标资源路径()
{
	return QStringLiteral(":/ICO/ICO/进度条.ico");
}