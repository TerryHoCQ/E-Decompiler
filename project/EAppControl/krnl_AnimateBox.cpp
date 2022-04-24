#include "krnl_AnimateBox.h"
#include "EAppControl.h"
#include "../common/public.h"

struct AnimateBox_UnitData
{
	unsigned int version;
	unsigned int 居中播放;
	unsigned int 透明背景;
	unsigned int 播放;
	int 播放次数;
	qstring 文件名;
};


QString krnl_AnimateBox::取图标资源路径()
{
	return QStringLiteral(":/ICO/ICO/影像框.ico");
}

void krnl_AnimateBox::反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	AnimateBox_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.居中播放 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.透明背景 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.播放 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.播放次数 = CDR_ReadInt(pUnitDataPtr);
	tmpData.文件名 = CDR_ReadCString(pUnitDataPtr);

	//——————————————————————————
	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("居中播放")] = tmpData.居中播放;
	out_data[QStringLiteral("透明背景")] = tmpData.透明背景;
	out_data[QStringLiteral("播放")] = tmpData.播放;
	out_data[QStringLiteral("播放次数")] = tmpData.播放次数;
	out_data[QStringLiteral("文件名")] = QString::fromLocal8Bit(tmpData.文件名.c_str());
}

void krnl_AnimateBox::取控件默认附加属性(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("居中播放")] = 1;
	out_data[QStringLiteral("透明背景")] = 1;
	out_data[QStringLiteral("播放")] = 1;
	out_data[QStringLiteral("播放次数")] = -1;
}

qstring krnl_AnimateBox::取事件名称(int eventIndex)
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

void krnl_AnimateBox::显示控件属性信息(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::添加文本控件(QStringLiteral("文件名"), map_ControlData[QStringLiteral("文件名")].toString());
	EAppControl::添加布尔控件(QStringLiteral("居中播放"), map_ControlData[QStringLiteral("居中播放")].toBool());
	EAppControl::添加布尔控件(QStringLiteral("透明背景"), map_ControlData[QStringLiteral("透明背景")].toBool());
	EAppControl::添加布尔控件(QStringLiteral("播放"), map_ControlData[QStringLiteral("播放")].toBool());
	EAppControl::添加布尔控件(QStringLiteral("播放次数"), map_ControlData[QStringLiteral("播放次数")].toBool());
}