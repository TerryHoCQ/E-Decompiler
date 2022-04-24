#include "krnl_VScrollBar.h"
#include "../common/public.h"

struct VScrollBar_UnitData
{
	unsigned int version;
	unsigned int 最小位置;
	unsigned int 最大位置;
	unsigned int 页改变值;
	unsigned int 行改变值;
	unsigned int 位置;
	unsigned int 允许拖动跟踪;
};

void krnl_VScrollBar::取控件默认附加属性(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("最小位置")] = 1;
	out_data[QStringLiteral("最大位置")] = 100;
	out_data[QStringLiteral("页改变值")] = 10;
	out_data[QStringLiteral("行改变值")] = 1;
	out_data[QStringLiteral("位置")] = 1;
	out_data[QStringLiteral("允许拖动跟踪")] = 1;
}

void krnl_VScrollBar::反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	VScrollBar_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.最小位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.最大位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.页改变值 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.行改变值 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.允许拖动跟踪 = CDR_ReadUInt(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("最小位置")] = tmpData.最小位置;
	out_data[QStringLiteral("最大位置")] = tmpData.最大位置;
	out_data[QStringLiteral("页改变值")] = tmpData.页改变值;
	out_data[QStringLiteral("行改变值")] = tmpData.行改变值;
	out_data[QStringLiteral("位置")] = tmpData.位置;
	out_data[QStringLiteral("允许拖动跟踪")] = tmpData.允许拖动跟踪;
}

void krnl_VScrollBar::显示控件属性信息(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::添加布尔控件(QStringLiteral("可停留焦点"), map_ControlData[QStringLiteral("可停留焦点")].toBool());
	EAppControl::添加文本控件(QStringLiteral("    停留顺序"), map_ControlData[QStringLiteral("停留顺序")].toString());
	EAppControl::添加文本控件(QStringLiteral("最小位置"), map_ControlData[QStringLiteral("最小位置")].toString());
	EAppControl::添加文本控件(QStringLiteral("最大位置"), map_ControlData[QStringLiteral("最大位置")].toString());
	EAppControl::添加文本控件(QStringLiteral("页改变值"), map_ControlData[QStringLiteral("页改变值")].toString());
	EAppControl::添加文本控件(QStringLiteral("行改变值"), map_ControlData[QStringLiteral("行改变值")].toString());
	EAppControl::添加文本控件(QStringLiteral("位置"), map_ControlData[QStringLiteral("位置")].toString());
	EAppControl::添加布尔控件(QStringLiteral("允许拖动跟踪"), map_ControlData[QStringLiteral("允许拖动跟踪")].toBool());
}

qstring krnl_VScrollBar::取事件名称(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "位置被改变";
		break;
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
	case -7:
		ret = "获得焦点";
		break;
	case -8:
		ret = "失去焦点";
		break;
	case -9:
		ret = "按下某键";
		break;
	case -10:
		ret = "放开某键";
		break;
	case -11:
		ret = "字符输入";
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

QString krnl_VScrollBar::取图标资源路径()
{
	return QStringLiteral(":/ICO/ICO/纵向滚动条.ico");
}